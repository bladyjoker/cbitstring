#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([bitstring], [0.0], [bladyjoker@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
LT_INIT

AC_CONFIG_SRCDIR([bitstring.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h malloc.h stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

CFLAGS=-std=c99
AC_CONFIG_FILES([Makefile
                 lua/Makefile])
AC_OUTPUT
