#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([Doggy], [0.1], [eleven17chen@163.com])
#AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR([src/hello2.cpp])
AM_INIT_AUTOMAKE

AC_PROG_CXX
AC_PROG_CC

# Checks for programs.

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_ENABLE(debug,
[ --enable-debug
          enable debug build]
[ enable_debug=$enableval ] ,
[debug_build=yes])

if test x"$enable_debug" = x"yes"
then
    CFLAGS=" -g -Wall -O0 "
    CXXFLAGS=" -g -Wall -O0 "
fi

AC_OUTPUT([Makefile
           src/Makefile
           ])

