
# Pawe� Pa�ucha pawel@praterm.com.pl
#
# $Id: Makefile.am 6635 2009-04-14 12:58:34Z pawel $

# No subdirectories
SUBDIRS = 

# Additional files for deleting on 'make maintainer-clean'
MAINTAINERCLEANFILES = Makefile.in

# Compilations flags
INCLUDES = @LUA_CFLAGS@ \
	   @XML_CFLAGS@ \
	   @BOOST_CPPFLAGS@ \
	   -I@srcdir@/../libSzarp/include \
	   -I@srcdir@/../libSzarp2/include \
	   -DPREFIX=\"@prefix@\"

LIBSZARP=../libSzarp/libSzarp.la \
	../libSzarp2/libSzarp2.la

LDADD = $(LIBSZARP) @XML_LIBS@ @BOOST_LDFLAGS@ @BOOST_FILESYSTEM_LIB@ @BOOST_THREAD_LIB@ @BOOST_DATE_TIME_LIB@ @BOOST_SYSTEM_LIB@

# Programs to create

bin_PROGRAMS = \
               sender

sender_SOURCES = sender.cc sender.h
               
