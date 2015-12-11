# Stop autoconf looking for readme file
AUTOMAKE_OPTIONS = foreign

# M4 Macros
ACLOCAL_AMFLAGS = -I ./m4 

AM_LDFLAGS =  $(AM_LFLAGS)

AM_CPPFLAGS = -I include/

# Main Program 
bin_PROGRAMS 	= dem_grain_gen

dem_grain_gen_SOURCES 	= src/main.cc
