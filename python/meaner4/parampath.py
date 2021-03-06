#!/usr/bin/python
# -*- coding: utf-8 -*-
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

import os
import param

class ParamPath:
	def __init__(self, param, szbase_dir):
		self.szbase_dir = szbase_dir
		self.param = param
		self.param_path = self.param_name_to_path(param.param_name)

	def param_name_to_path(self, param_name):
		def conv(x):
			if x in [ u"0", u"1", u"2", u"3", u"4", u"5", u"6", u"7", u"8", u"9",
				  u"a", u"b", u"c", u"d", u"e", u"f", u"g", u"h", u"i", u"j",
				  u"k", u"l", u"m", u"n", u"o", u"p", u"q", u"r", u"s", u"t",
				  u"u", u"v", u"w", u"x", u"y", u"z",
				  u"A", u"B", u"C", u"D", u"E", u"F", u"G", u"H", u"I", u"J",
			          u"K", u"L", u"M", u"N", u"O", u"P", u"Q", u"R", u"S", u"T",
				  u"U", u"V", u"W", u"X", u"Y", u"Z"]:
				return x

			if x == u":":
				return "/"

			pmap = { u"ą" : u"a", u"Ą" : u"A", u"ć" : u"c", u"Ć" : u"C",
				 u"ę" : u"e", u"Ę" : u"E", u"ł" : u"l", u"Ł" : u"L",
				 u"ń" : u"n", u"Ń" : u"N", u"ó" : u"o", u"Ó" : u"O",
				 u"ż" : u"z", u"Ż" : u"Z", u"ź" : u"z", u"Ź" : u"Z" }

			if x in pmap:
				return pmap[x]

			return u"_"
				
		return "".join([ conv(x) for x in param_name ])

	def create_file_path(self, time, nanotime):
		if self.param.time_prec == 4:
			file_name = "%010d.sz4" % (time)
		else:
			file_name = "%010d%010d.sz4" % (time, nanotime)
		return os.path.join(self.szbase_dir, self.param_path, file_name)

	def param_dir(self):
		return os.path.join(self.szbase_dir, self.param_path)

	def find_latest_path(self):
		try:
			file_names = os.listdir(self.param_dir())
			file_names.sort()

			if len(file_names) > 0:
				return os.path.join(self.szbase_dir, self.param_path, file_names[-1])
			else:
				return None
		except OSError:
			return None
