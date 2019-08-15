## ============================================================
##
## Configuration file
##
## Copyright (c) Yinka Ashon 2016
##
## ============================================================
AC_PREREQ([2.69])
AC_INIT([file-inspector], [0.0.4], [gigalimit20@yahoo.com])

AM_PROG_AR
LT_INIT

## Files
AC_CONFIG_SRCDIR([src/common.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	man/Makefile
        test/Makefile
	src/Makefile
        src/lib/Makefile
        src/inspector/Makefile
])


# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
PKG_CHECK_MODULES([FI_DEPS], [glib-2.0 gobject-2.0])


## Automake things
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AC_CONFIG_MACRO_DIRS([m4])

AC_OUTPUT

printf "\n\nAll good\n"
