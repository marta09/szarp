/* 
 * SZARP: SCADA software 
 *
 * Copyright (C) 
 * 2011 - Jakub Kotur <qba@newterm.pl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
 /** 
 * @file logdmn.cc
 * @brief Daemon for remote logging users activity.
 * @author Jakub Kotur <qba@newterm.pl>
 * @version 0.1
 * @date 2011-06-15
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <liblog.h>

#include "basedmn.h"

class SampleDaemon : public BaseDaemon {
public:
	SampleDaemon() : BaseDaemon("sampledmn")
	{
	}

	virtual ~SampleDaemon()
	{
	}

	virtual void Read()
	{
		for( unsigned int i=0 ; i<Length() ; ++i )
			Set( i , 1 );
	}

	virtual int ParseConfig(DaemonConfig * cfg)
	{
		return 0;
	}
};

int main(int argc, const char *argv[])
{
	SampleDaemon dmn;

	if( dmn.Init( argc , argv ) ) {
		sz_log(0,"Cannot start daemon");
		return 1;
	}

	sz_log(2, "Starting %s",dmn.Name());

	for(;;)
	{
		dmn.Wait();
		dmn.Read();
		dmn.Transfer();
	}

	return 0;
}
