AC_INIT([addition], [1.0], [youremail@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CC
AM_PROG_CC_C_O

# gettext for l18n
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.20])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    tests/Makefile
    po/Makefile.in
    doc/Makefile
])
AC_OUTPUT
