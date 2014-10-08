lib_LTLIBRARIES = libOsiconic.la

libOsiconic_la_SOURCES=\
	OsiConicSolverInterface.hpp\
	OsiConicSolverInterface.cpp\
	OsiConicCut.hpp\
	OsiConicCut.cpp\
	OsiConicCuts.hpp\
	OsiConicCuts.cpp

libOsiconic_la_LIBADD=\
	$(OSI_LIBS)\
	$(COINUTILS_LIBS)\
	$(LIBS)

AM_CPPFLAGS=\
	-I../../include\
	$(OSI_CFLAGS)\
	$(COINUTILS_CFLAGS)


# header files to be installed to $(includedir)
include_HEADERS=\
	OsiConicSolverInterface.hpp\
	OsiConicCut.hpp\
	OsiConicCuts.hpp

# this are in the disctribution but not in include
#noinst_HEADERS=
