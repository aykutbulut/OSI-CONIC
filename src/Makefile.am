AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libOsiConic.la

libOsiConic_la_SOURCES=\
	OsiConicSolverInterface.hpp\
	OsiConicSolverInterface.cpp\
	OsiConicCut.hpp\
	OsiConicCut.cpp\
	OsiConicCuts.hpp\
	OsiConicCuts.cpp

libOsiConic_la_LIBADD=\
	$(OSI_LIBS)\
	$(COINUTILS_LIBS)\
	$(LIBS)

# This is for libtool
libOsiConic_la_LDFLAGS = $(LT_LDFLAGS)

# This line is necessary to allow VPATH compilation
DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)`

AM_CPPFLAGS=\
	-I$(includedir)/coin\
	$(OSI_CFLAGS)\
	$(COINUTILS_CFLAGS)\
	$(OSICONICLIB_CFLAGS)

includecoindir = $(includedir)/coin

includecoin_HEADERS = \
	OsiConicSolverInterface.hpp\
	OsiConicCut.hpp\
	OsiConicCuts.hpp

# this are in the distribution but not in include
#noinst_HEADERS=
