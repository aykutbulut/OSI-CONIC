# Copyright (C) 2015 Lehigh University.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

# Author:  Aykut Bulut, Lehigh University 2015-05-22

AUTOMAKE_OPTIONS = foreign

########################################################################
#                               libOsiConic                            #
########################################################################

# Name of the library compiled in this directory.  We want it to be installed
# in the 'lib' directory
lib_LTLIBRARIES = libOsiConic.la

# List all source files for this library, including headers
libOsiConic_la_SOURCES=\
	Cone.hpp\
	LorentzCone.hpp\
	ScaledCone.hpp\
	OsiConicSolverInterface.hpp\
	OsiConicSolverInterface.cpp\
	OsiConicCut.hpp\
	OsiConicCut.cpp\
	OsiConicCuts.hpp\
	OsiConicCuts.cpp

# List all additionally required libraries
if DEPENDENCY_LINKING
libOsiConic_la_LIBADD = $(OSICONICLIB_LIBS)
endif

# This is for libtool
libOsiConic_la_LDFLAGS = $(LT_LDFLAGS)

# Here list all include flags.
AM_CPPFLAGS = $(COINUTILS_CFLAGS)\
	 $(OSI_CFLAGS)

########################################################################
#                            Additional flags                          #
########################################################################

# This line is necessary to allow VPATH compilation
DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)`

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin'
includecoindir = $(includedir)/coin
includecoin_HEADERS = \
	Cone.hpp\
	LorentzCone.hpp\
	ScaledCone.hpp\
	OsiConicSolverInterface.hpp\
	OsiConicCut.hpp\
	OsiConicCuts.hpp

install-exec-local:
	$(install_sh_DATA) config_osiconic.h $(DESTDIR)$(includecoindir)/OsiConicConfig.h

uninstall-local:
	rm -f $(DESTDIR)$(includecoindir)/OsiConicConfig.h
