"""
  SZARP: SCADA software 
  Darek Marcinkiewicz <reksio@newterm.pl>

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

"""

import zmq
import lxml
import paramsvalues_pb2
import param
import saveparam

class Meaner:
	def __init__(self, path, uri):
		self.save_params = []

		self.szbase_path = szbase_path
		self.parcook_uri = uri

		self.context = zmq.Context(1)
		self.socket = self.context.socket(zmq.SUB)

	def configure(self, ipk_path):
		ipk = lxml.etree.parse(ipk_path)
		
		for p in ipk.xpath("//s:param", namespaces={'s':'http://www.praterm.com.pl/SZARP/ipk'}):
			self.save_params.append(saveparam.SaveParam(param.Param(p), self.szbase_path))

	def run(self):
		self.socket.connect(self.parcook_uri)

		while True:
			msg = self.socket.recv()

			params_values = ParamsValues()
			params_values.ParseFromString(msg)

			for param_value in params_values.param_values:
				self.save_params[param_value.param_no].process_value(param_value)
			
