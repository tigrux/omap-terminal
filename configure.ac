AC_INIT([omap-terminal], [0.1], [tigrux@gmail.com], [omap-terminal])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_DISABLE_STATIC

AC_PATH_PROG(VALAC, valac, valac)
AC_SUBST(VALAC)

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

VALA_DEPS="--pkg gtk+-2.0 --pkg vte"
AC_SUBST(VALA_DEPS)

PKG_CHECK_MODULES(PROGRAM, 
    gtk+-2.0
    gio-2.0
    vte
    )
AC_SUBST(PROGRAM_CFLAGS)
AC_SUBST(PROGRAM_LIBS)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	])

AC_OUTPUT

