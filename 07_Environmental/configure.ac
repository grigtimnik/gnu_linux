#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [google@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])


AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([RHASH], [librhash >= 1.3.0],, [AC_MSG_ERROR([librhash is required.])])

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--enable-readline], [enable support for readline (default: yes)])],
  [], [enable_readline=yes])


USE_READLINE=no
AM_CONDITIONAL([USE_READLINE], [test "x$enable_readline" = "xyes"])
if test "x$enable_readline" = "xyes"; then
  PKG_CHECK_MODULES([READLINE], [readline], [
    USE_READLINE=yes
    AC_DEFINE([HAVE_READLINE], [1], [Define if using readline])],
    [AC_MSG_NOTICE([readline not found, continuing without it])])
fi


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strcspn])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
