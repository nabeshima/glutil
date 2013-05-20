#
# $Id$
# Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
# This file is subject to the MIT license available at,
# http://opensource.org/licenses/mit-license.php
#

include ../../Makefile.usrdef

TARGETS= \
	main.exe \


ifneq (${shell if pkg-config --exists x11; then echo DUMMY; fi},)
XGL_CFLAGS=`pkg-config --cflags x11`
XGL_LDFLAGS=`pkg-config --libs x11`
endif

CFLAGS=-I$(INSTALLPATH)/include/glutil $(USR_CFLAGS) $(XGL_CFLAGS)
LDFLAGS=-L$(INSTALLPATH)/lib -lglutil $(USR_LDFLAGS) $(XGL_LDFLAGS)

all: $(TARGETS)

$(TARGETS): main.o Robot.o
	$(CXX) main.o Robot.o $(CFLAGS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CFLAGS) -o $@

install uninstall:

clean distclean:
	rm -rf *~ .#* *.dSYM $(TARGETS) *.o
