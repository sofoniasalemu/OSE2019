# Copyright (C) 2009 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

# $Id: Makefile.in 1135 2007-12-27 19:23:06Z andreasw $

##########################################################################
#    You can modify this example makefile to fit for your own program.   #
#    Usually, you only need to change the five CHANGEME entries below.   #
##########################################################################

# CHANGEME: This should be the name of your executable
EXE = TutorialFortran

# CHANGEME: Here is the name of all object files corresponding to the source
#           code that you wrote in order to define the problem statement
OBJS = TutorialFortran.o

# CHANGEME: Additional libraries
ADDLIBS =

# CHANGEME: Additional flags for compilation (e.g., include flags)
ADDINCFLAGS =

# Directory to the sources for the (example) problem definition files
SRCDIR = .
VPATH = .

##########################################################################
#  Usually, you don't have to change anything below.  Note that if you   #
#  change certain compiler options, you might have to recompile Ipopt.   #
##########################################################################

# Fortran Compiler options
F77 = gfortran

# Fotran Compiler options
FFLAGS = -O3 -pipe  

# additional Fortran Compiler options for linking
F77LINKFLAGS =  -Wl,--rpath -Wl,/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib

# Include directories (we use the CYGPATH_W variables to allow compilation with Windows compilers)
INCL = `PKG_CONFIG_PATH=/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib64/pkgconfig:/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib/pkgconfig:/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/share/pkgconfig:/software/python-2.7.12-el7-x86_64/lib/pkgconfig:/software/openmpi-2.0.1-el7-x86_64/lib/pkgconfig:/software/serf-1.3.9-el7-x86_64/lib/pkgconfig pkg-config --cflags ipopt` $(ADDINCFLAGS)
#INCL = -I`$(CYGPATH_W) /home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/include/coin`  $(ADDINCFLAGS)

# Linker flags
LIBS = `PKG_CONFIG_PATH=/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib64/pkgconfig:/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib/pkgconfig:/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/share/pkgconfig:/software/python-2.7.12-el7-x86_64/lib/pkgconfig:/software/openmpi-2.0.1-el7-x86_64/lib/pkgconfig:/software/serf-1.3.9-el7-x86_64/lib/pkgconfig pkg-config --libs ipopt` -lstdc++ -lm
#LIBS = -L/home/rccguest2912/OSE2019/day1/SparseGridCode/pyipopt_midway/Ipopt-3.12.5/build/lib -lipopt -llapack -lblas -lm  -ldl -lstdc++ -lm

# The following is necessary under cygwin, if native compilers are used
CYGPATH_W = echo

all: $(EXE)

.SUFFIXES: .f .o .obj

$(EXE): $(OBJS)
	bla=;\
	for file in $(OBJS); do bla="$$bla `$(CYGPATH_W) $$file`"; done; \
	$(F77) $(F77LINKFLAGS) $(FFLAGS) -o $@ $$bla $(ADDLIBS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS) IPOPT.OUT

.f.o:
	$(F77) $(FFLAGS) $(INCL) -c -o $@ $<


.f.obj:
	$(F77) $(FFLAGS) $(INCL) -c -o $@ `$(CYGPATH_W) '$<'`
