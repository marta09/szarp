/*
  SZARP: SCADA software 

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
/* 
 * $Id$
 */
/*
 @description_start
 @class 4
 @devices Kamstrup Multical IV, Kamstrup Multical 66CDE heatmeters.
 @devices.pl Ciep�omierz Kamstrup Multical IV, Kamstrup Multical 66CDE.

 @description_end
*/

/* "Publiczne udost�pnianie protoko�u do licznik�w Multical III i Multical 66C nie jest zabronione. Ograniczenia s� zwi�zane tylko z protoko�em KMP (do licznik�w Multical 601 i nowszych)." (Kamstrup, 04.12.2012) */
 
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <event.h>
#include <libgen.h>
#include <boost/tokenizer.hpp>

#include "liblog.h"
#include "xmlutils.h"
#include "conversion.h"
#include "ipchandler.h"
#include "serialport.h"

#ifndef SZARP_NO_DATA
#define SZARP_NO_DATA -32768
#endif

#define NUMBER_OF_TOKENS 10
#define NUMBER_OF_VALS 16

#define RESPONSE_SIZE 82

bool single;

void dolog(int level, const char * fmt, ...)
	__attribute__ ((format (printf, 2, 3)));


void dolog(int level, const char * fmt, ...) {
	va_list fmt_args;

	if (single) {
		char *l;
		va_start(fmt_args, fmt);
		vasprintf(&l, fmt, fmt_args);
		va_end(fmt_args);

		std::cout << l << std::endl;
		sz_log(level, "%s", l);
		free(l);
	} else {
		va_start(fmt_args, fmt);
		vsz_log(level, fmt, fmt_args);
		va_end(fmt_args);
	}
} 

xmlChar* get_device_node_prop(xmlXPathContextPtr xp_ctx, const char* prop) {
	xmlChar *c;
	char *e;
	asprintf(&e, "./@%s", prop);
	assert (e != NULL);
	c = uxmlXPathGetProp(BAD_CAST e, xp_ctx);
	free(e);
	return c;
}

xmlChar* get_device_node_extra_prop(xmlXPathContextPtr xp_ctx, const char* prop) {
	xmlChar *c;
	char *e;
	asprintf(&e, "./@extra:%s", prop);
	assert (e != NULL);
	c = uxmlXPathGetProp(BAD_CAST e, xp_ctx);
	free(e);
	return c;
}

/** Daemon reading data from heatmeters.
 * Can use either a SerialPort (if 'path' is declared in params.xml)
 * or a SerialAdapter connection
 * (if 'extra:tcp-ip' and optionally 'extra:tcp-data-port' and 'extra:tcp-cmd-port' are declared)
 */
class kams_daemon: public SerialPortListener {
public:
	typedef enum {MODE_B300, MODE_B1200_EVEN, MODE_B1200} SerialMode;
	typedef enum {SET_COMM_WRITE, WRITE, REPEAT_WRITE, SET_COMM_READ, READ, RESTART} CommunicationState;

	class KamsDmnException : public MsgException { } ;
	class NoDataException : public KamsDmnException { } ;

	kams_daemon() : m_daemon_conf(NULL), m_ipc(NULL),
			m_state(SET_COMM_WRITE),
			m_read_mode(MODE_B1200_EVEN),
			m_chars_written(0),
			m_wait_for_data_ms(6000),
			m_path(""),
			m_ip(""),
			m_serial_port(NULL)
	{
		m_query_command.push_back('/');
		m_query_command.push_back('#');
		m_query_command.push_back('1');
	}

	~kams_daemon()
	{
		if (m_daemon_conf != NULL) {
			delete m_daemon_conf;
		}
		if (m_ipc != NULL) {
			delete m_ipc;
		}
		if (m_serial_port != NULL) {
			delete m_serial_port;
		}
	}

	/** Read commandline and params.xml configuration */
	void ReadConfig(int argc, char **argv);

	/** Start event-based state machine */
	void StartDo();

protected:
	/** Schedule next state machine step */
	void ScheduleNext(unsigned int wait_ms);

        /** Callback for next step of timed state machine. */
        static void TimerCallback(int fd, short event, void* thisptr);

	/** One step of state machine */
	void Do();

	/** Sets NODATA and schedules reconnect */
	void SetRestart()
	{
		m_state = RESTART;
		for (int i = 0; i < m_ipc->m_params_count; i++) {
			m_ipc->m_read[i] = SZARP_NO_DATA;
		}
		m_ipc->GoParcook();
	}

	/** Write single char of query command to device */
	void WriteChar();

	/** SerialPortListener interface */
	virtual void ReadError(short event);
	virtual void ReadData(const std::vector<unsigned char>& data);
	virtual void ConfigurationWasSet()
	{}

	/** Increase wait for data time */
	void IncreaseWaitForDataTime();

	/** Process received data */
	void ProcessResponse();

	/** Helper method for ProcessResponse */
	std::vector<std::string> SplitMessage();

	/** Sets serial communication mode - changes SerialAdapter configuration */
	void SelectSerialMode(SerialMode mode);

	/** Switches read mode to be used in next read */
	void SwitchSerialReadMode()
	{
		if (m_read_mode == MODE_B1200_EVEN) {
			m_read_mode = MODE_B1200;
		} else {
			m_read_mode = MODE_B1200_EVEN;
		}
	}

protected:
	DaemonConfig *m_daemon_conf;
	IPCHandler *m_ipc;

	CommunicationState m_state;	/**< state of communication state machine */
	SerialMode m_read_mode;		/**< serial comm mode currently used */
	struct event m_ev_timer;
					/**< event timer for calling QueryTimerCallback */

	std::vector<unsigned char> m_query_command;
					/**< commmand used for communication with device */
	unsigned int m_chars_written;	/**< counter of number of chars written to device */
	unsigned int m_query_interval_ms;
					/**< interval between single queries */
	unsigned int m_wait_for_data_ms;/**< time for which daemon waits for data from Kamstrup meter */

	std::string m_read_buffer;	/**< buffer for data received from Kamstrup meter */
	std::vector<unsigned int> m_params;
					/**< numeric values of received params */

	std::string m_id;		/**< ID of given kamsdmn */

	std::string m_path;		/**< Serial port file descriptor path */

	std::string m_ip;		/**< SerialAdapter ip */
	int m_data_port;		/**< SerialAdapter data port number */
	int m_cmd_port;			/**< SerialAdapter command port number */

	BaseSerialPort *m_serial_port;
};

void kams_daemon::StartDo() {
	try {
		if (m_ip.compare("") != 0) {
			SerialAdapter *client = new SerialAdapter();
			m_serial_port = client;
			client->InitTcp(m_ip, m_data_port, m_cmd_port);
		} else {
			SerialPort *port = new SerialPort();
			m_serial_port = port;
			port->Init(m_path);
		}
		m_serial_port->AddListener(this);
		m_serial_port->Open();
		std::string info = m_id + ": connection established.";
		dolog(2, "%s: %s", m_id.c_str(), info.c_str());
	} catch (SerialPortException &e) {
		dolog(0, "%s: %s", m_id.c_str(), e.what());
		SetRestart();
	}
        evtimer_set(&m_ev_timer, TimerCallback, this);
	Do();
}

void kams_daemon::Do()
{
	unsigned int wait_ms = 0;
	switch (m_state) {
		case SET_COMM_WRITE:
			SelectSerialMode(MODE_B300);
			m_read_buffer.clear();
			m_chars_written = 0;
			m_state = WRITE;
			wait_ms = 2000;
			break;
		case WRITE:
			try {
				WriteChar();
			} catch (SerialPortException &e) {
				dolog(0, "%s: %s", m_id.c_str(), e.what());
				SetRestart();
			}
			if (m_chars_written == 3) {
				m_chars_written = 0;
				m_state = REPEAT_WRITE;
			}
			wait_ms = 50;
			break;
		case REPEAT_WRITE:
			try {
				WriteChar();
			} catch (SerialPortException &e) {
				dolog(0, "%s: %s", m_id.c_str(), e.what());
				SetRestart();
			}
			if (m_chars_written < 3) {
				wait_ms = 50;
			} else {
				m_state = SET_COMM_READ;
				wait_ms = 10;
			}
			break;
		case SET_COMM_READ:
			SelectSerialMode(m_read_mode);
			m_state = READ;
			wait_ms = m_wait_for_data_ms;
			dolog(10, "%s: waiting for data, wait time = %dms", m_id.c_str(),
				m_wait_for_data_ms);
			break;
		case READ:
			try {
				ProcessResponse();
				wait_ms = m_query_interval_ms;
				m_state = SET_COMM_WRITE;
				for (int i = 0; i < m_ipc->m_params_count; i++) {
					m_ipc->m_read[i] = m_params.at(i);
				}
				m_ipc->GoParcook();
			} catch (NoDataException &e) {
				dolog(0, "%s: %s", m_id.c_str(), e.what());
				wait_ms = 0;
				IncreaseWaitForDataTime();
				SetRestart();
			} catch (KamsDmnException &e) {
				dolog(0, "%s: %s", m_id.c_str(), e.what());
				wait_ms = 1000;
				m_state = SET_COMM_WRITE;
				for (int i = 0; i < m_ipc->m_params_count; i++) {
					m_ipc->m_read[i] = SZARP_NO_DATA;
				}
				m_ipc->GoParcook();
			} catch (SerialPortException &e) {
				dolog(0, "%s: %s", m_id.c_str(), e.what());
				wait_ms = 0;
				IncreaseWaitForDataTime();
				SetRestart();
			}
			break;
		case RESTART:
			try {
				m_serial_port->Close();
				m_serial_port->Open();
				dolog(2, "%s: %s", m_id.c_str(), "Restart successful!");
				m_state = SET_COMM_WRITE;
			} catch (SerialPortException &e) {
				dolog(0, "%s: %s %s", m_id.c_str(), "Restart failed:", e.what());
				for (int i = 0; i < m_ipc->m_params_count; i++) {
					m_ipc->m_read[i] = SZARP_NO_DATA;
				}
				m_ipc->GoParcook();
			}
			wait_ms = 15 * 1000;
			break;
	}
	ScheduleNext(wait_ms);
}

void kams_daemon::SelectSerialMode(SerialMode mode)
{
	struct termios serial_conf;
	serial_conf.c_iflag = 0;
	serial_conf.c_oflag = 0;

	switch (mode) {
		case MODE_B300:
			serial_conf.c_cflag = B300 | CS7 | CSTOPB | CLOCAL | CREAD;
			break;
		case MODE_B1200_EVEN:
			serial_conf.c_cflag = B1200 | CS7 | CSTOPB | PARENB | CLOCAL | CREAD;
			break;
		case MODE_B1200:
			serial_conf.c_cflag= B1200 | CS7 | CSTOPB | CLOCAL | CREAD;
			break;
	}
	serial_conf.c_lflag = 0;
	serial_conf.c_cc[4] = 100;
	serial_conf.c_cc[5] = 100;

	m_serial_port->SetConfiguration(&serial_conf);
}

void kams_daemon::WriteChar()
{
	unsigned char c = m_query_command.at(m_chars_written);
	m_serial_port->WriteData(&c, 1);
	m_chars_written++;
}

void kams_daemon::ReadError(short event)
{
	dolog(0, "%s: %s", m_id.c_str(), "ReadError, closing connection..");
	m_serial_port->Close();
	SetRestart();
}

void kams_daemon::ReadData(const std::vector<unsigned char>& data)
{
	m_read_buffer.insert(m_read_buffer.end(), data.begin(), data.end());
}

void kams_daemon::IncreaseWaitForDataTime()
{
	unsigned int max_ms = 30 * 1000;
	unsigned int step_ms = 6 * 1000;
	if (m_wait_for_data_ms < max_ms)
		m_wait_for_data_ms += step_ms;
}

void kams_daemon::ProcessResponse()
{
	m_params.clear();
	m_params.resize(NUMBER_OF_VALS, SZARP_NO_DATA);

	unsigned int message_size = RESPONSE_SIZE - 3;			// ' ',CR,LF
	unsigned int expected_response_size = RESPONSE_SIZE - 1;	// LF isn't read by bufferevent

	if (m_read_buffer.size() == expected_response_size) {
		m_read_buffer.resize(message_size);
		if (m_daemon_conf->GetSingle()) {
			std::cout << "Frame received: \"" << m_read_buffer << '"' << std::endl;
		}
	} else if (m_read_buffer.size() == 0) {
		NoDataException ex;
		ex.SetMsg("ERROR!: No data was read from socket.");
		throw ex;
	} else {
		SwitchSerialReadMode();					// try with another parity next time
		KamsDmnException ex;
		ex.SetMsg("ERROR!: Frame size %d is incorrect (%d)", m_read_buffer.size(), expected_response_size);
		throw ex;
	}

	std::vector<std::string> tokens = SplitMessage();
	for (unsigned int i = 0; i < tokens.size(); i++) {
		std::istringstream istr(tokens[i]);
		unsigned int kamdata;
		bool conversion_failed = (istr >> kamdata).fail();
		if (conversion_failed) {
			SwitchSerialReadMode();
			KamsDmnException ex;
			ex.SetMsg("ERROR!: Couldn't parse token nr %d", i);
			throw ex;
		}
		switch (i) {
		case 0:	/* energy in 0.1 GJ - 4 bytes */
			m_params[0] = (int)(kamdata & 0xffff);
			m_params[1] = (int)(kamdata >> 16);
			break;
		case 1:	/* water in m3 - 4 bytes */
			m_params[2] = (int)(kamdata & 0xffff);
			m_params[3] = (int)(kamdata >> 16);
			break;
		case 2:	/* time in hours - 4 bytes */
			m_params[4] = (int)(kamdata & 0xffff);
			m_params[5] = (int)(kamdata >> 16);
			break;
		case 3:	/* feed water temp. in C degrees - 2 bytes */
			m_params[6] = (int)kamdata;
			break;
		case 4:	/* return water temp. in C degrees - 2 bytes */
			m_params[7] = (int)kamdata;
			break;
		case 5:	/* water temp. difference in C degrees - 2 bytes */
			m_params[8] = (int)kamdata;
			break;
		case 6:	/* power in 0.1 kW - 4 bytes */
			m_params[9] = (int)(kamdata & 0xffff);
			m_params[10] = (int)(kamdata >> 16);
			break;
		case 7:	/* flow in liters per hour - 4 bytes */
			m_params[11] = (int)(kamdata & 0xffff);
			m_params[12] = (int)(kamdata >> 16);
			break;
		case 8:	/* peak power in 0.1 kW - 4 bytes */
			m_params[13] = (int)(kamdata & 0xffff);
			m_params[14] = (int)(kamdata >> 16);
			break;
		default:	/* case 9: info - 2 bytes */
			m_params[15] = (int)kamdata;
			break;
		}
	}
	if (tokens.size() != NUMBER_OF_TOKENS) {
		KamsDmnException ex;
		ex.SetMsg("ERROR!: Received %d values instead of %d", tokens.size(), NUMBER_OF_TOKENS);
		throw ex;
	}
}

std::vector<std::string> kams_daemon::SplitMessage()
{
	// use boost::tokenizer to split message at each space
	typedef boost::tokenizer<boost::char_separator<char> > tok_t;
	boost::char_separator<char> sep(" ", "", boost::keep_empty_tokens);
	tok_t tok(m_read_buffer, sep);
	std::vector<std::string> tokens;
	for(tok_t::iterator it = tok.begin(); it != tok.end(); ++it)
		tokens.push_back(*it);
	return tokens;
}

void kams_daemon::ScheduleNext(unsigned int wait_ms)
{
	struct timeval tv;
	tv.tv_sec = wait_ms / 1000;
	tv.tv_usec = (wait_ms % 1000) * 1000;
	evtimer_add(&m_ev_timer, &tv);
}

void kams_daemon::TimerCallback(int fd, short event, void* thisptr)
{
        reinterpret_cast<kams_daemon*>(thisptr)->Do();
}

void kams_daemon::ReadConfig(int argc, char **argv) {
	xmlInitParser();
	LIBXML_TEST_VERSION
	xmlLineNumbersDefault(1);
	
	m_daemon_conf = new DaemonConfig("kamsdmn");
	assert(m_daemon_conf != NULL);
	if (m_daemon_conf->Load(&argc, argv)) {
		KamsDmnException ex;
		ex.SetMsg("Cannot load configuration");
		throw ex;
	}
	if (m_daemon_conf->GetDevice()->GetFirstRadio()->
			GetFirstUnit()->GetParamsCount() 
			!= NUMBER_OF_VALS) {
		KamsDmnException ex;
		ex.SetMsg("Incorrect number of parameters: %d, must be %d",
				m_daemon_conf->GetDevice()->GetFirstRadio()->
				GetFirstUnit()->GetParamsCount(),
				NUMBER_OF_VALS);
		throw ex;
	}

	m_ipc = new IPCHandler(m_daemon_conf);
	if (!m_daemon_conf->GetSingle()) {
		if (m_ipc->Init()) {
			KamsDmnException ex;
			ex.SetMsg("Cannot initialize IPCHandler");
			throw ex;
		}
	}
	if (m_daemon_conf->GetSingle())
		m_query_interval_ms = 1000;
	else
		m_query_interval_ms = 280 * 1000;	/* for saving heatmeter battery */


	xmlDocPtr doc;

	/* get config data */
	doc = m_daemon_conf->GetXMLDoc();
	assert (doc != NULL);

	/* prepare xpath */
	xmlXPathContextPtr xp_ctx = xmlXPathNewContext(doc);
	assert (xp_ctx != NULL);
	int ret = xmlXPathRegisterNs(xp_ctx, BAD_CAST "ipk",
			SC::S2U(IPK_NAMESPACE_STRING).c_str());
	assert (ret == 0);
	ret = xmlXPathRegisterNs(xp_ctx, BAD_CAST "extra",
			BAD_CAST IPKEXTRA_NAMESPACE_STRING);
	assert (ret == 0);

	xp_ctx->node = m_daemon_conf->GetXMLDevice();

	xmlChar *c = get_device_node_extra_prop(xp_ctx, "tcp-ip");
	if (c == NULL) {
		xmlChar *path = get_device_node_prop(xp_ctx, "path");
		if (path == NULL) {
			KamsDmnException ex;
			ex.SetMsg("ERROR!: neither IP nor device path has been specified");
			throw ex;
		}
		m_path.assign((const char*)path);
		xmlFree(path);

		m_id = m_path;
	} else {
		m_ip.assign((const char*)c);
		xmlFree(c);

		xmlChar* tcp_data_port = get_device_node_extra_prop(xp_ctx, "tcp-data-port");
		if (tcp_data_port == NULL) {
			m_data_port = SerialAdapter::DEFAULT_DATA_PORT;
			dolog(2, "Unspecified tcp data port, assuming default port: %hu", m_data_port);
		} else {
			std::istringstream istr((char*) tcp_data_port);
			bool conversion_failed = (istr >> m_data_port).fail();
			if (conversion_failed) {
				KamsDmnException ex;
				ex.SetMsg("ERROR!: Invalid data port value: %s", tcp_data_port);
				throw ex;
			}
		}
		xmlFree(tcp_data_port);

		xmlChar* tcp_cmd_port = get_device_node_extra_prop(xp_ctx, "tcp-cmd-port");
		if (tcp_cmd_port == NULL) {
			m_cmd_port = SerialAdapter::DEFAULT_CMD_PORT;
			dolog(2, "Unspecified cmd port, assuming default port: %hu", m_cmd_port);
		} else {
			std::istringstream istr((char*) tcp_cmd_port);
			bool conversion_failed = (istr >> m_cmd_port).fail();
			if (conversion_failed) {
				KamsDmnException ex;
				ex.SetMsg("ERROR!: Invalid cmd port value: %s", tcp_cmd_port);
				throw ex;
			}
		}
		xmlFree(tcp_cmd_port);

		std::stringstream istr;
		std::string data_port_str;
		istr << m_data_port;
		istr >> data_port_str;
		m_id = m_ip + ":" + data_port_str;
	}
	single = m_daemon_conf->GetSingle() || m_daemon_conf->GetDiagno();
}

int main(int argc, char *argv[])
{
	event_init();
	kams_daemon daemon;

	try {
		daemon.ReadConfig(argc, argv);
	} catch (kams_daemon::KamsDmnException &e) {
		dolog(0, e.what());
		exit(1);
	}
	daemon.StartDo();

	try {
		event_dispatch();
	} catch (MsgException &e) {
		dolog(0, "FATAL!: daemon killed by exception: %s", e.what());
		exit(1);
	} catch (...) {
		dolog(0, "FATAL!: daemon killed by unknown exception");
		exit(1);
	}
}
