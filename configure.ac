AC_PREREQ(2.62)

AC_INIT([mate-menus], [1.26.1], [https://mate-desktop.org])
AC_CONFIG_SRCDIR(libmenu/matemenu-tree.h)

AM_INIT_AUTOMAKE([1.9 foreign no-dist-gzip dist-xz check-news])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS(config.h)

AM_MAINTAINER_MODE
MATE_MAINTAINER_MODE_DEFINES
MATE_DEBUG_CHECK([no])
MATE_COMPILE_WARNINGS

# Before making a release, the LT_VERSION string should be modified.
# The string is of the form C:R:A.
# - If interfaces have been changed or added, but binary compatibility has
#   been preserved, change to C+1:0:A+1
# - If binary compatibility has been broken (eg removed or changed interfaces)
#   change to C+1:0:0
# - If the interface is the same as the previous version, change to C:R+1:A

LIB_MENU_LT_VERSION=6:9:4
AC_SUBST(LIB_MENU_LT_VERSION)

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.8])
AM_CONDITIONAL([USE_NLS], [test "x${USE_NLS}" = "xyes"])

GETTEXT_PACKAGE=AC_PACKAGE_NAME
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Name of default gettext domain])
AC_SUBST(GETTEXT_PACKAGE)

AC_PROG_CC
AC_STDC_HEADERS
AC_ARG_PROGRAM
AM_PROG_LIBTOOL

PKG_CHECK_MODULES(GIO_UNIX, gio-unix-2.0 >= 2.50.0)
AC_SUBST(GIO_UNIX_CFLAGS)
AC_SUBST(GIO_UNIX_LIBS)

AC_ARG_ENABLE(collection,
  AC_HELP_STRING([--enable-collection],
                 [enable collection menu entry]),,
  enable_collection=yes)

if test x$enable_collection = xyes; then
    AC_DEFINE(WITH_COLLECTION,1,[Build with collection menu entry support])
fi

AC_ARG_ENABLE(deprecation_flags,
              [AC_HELP_STRING([--enable-deprecation-flags],
                              [use *_DISABLE_DEPRECATED flags @<:@default=no@:>@])],,
              [enable_deprecation_flags=no])

if test "x$enable_deprecation_flags" = "xyes"; then
   DISABLE_DEPRECATED_CFLAGS=$DISABLE_DEPRECATED
   AC_SUBST(DISABLE_DEPRECATED_CFLAGS)
fi

dnl ---------------------------------------------------------------------------
dnl - logging
dnl ---------------------------------------------------------------------------
if test "$ax_enable_debug" = "yes"; then
  DEBUG_CFLAGS="-DG_ENABLE_DEBUG"
else
  if test "x$ax_enable_debug" = "xno"; then
    DEBUG_CFLAGS="-DG_DISABLE_ASSERT -DG_DISABLE_CHECKS"
  else
    DEBUG_CFLAGS=""
  fi
fi
AC_SUBST(DEBUG_CFLAGS)

GOBJECT_INTROSPECTION_CHECK([0.6.7])

AC_OUTPUT([
Makefile
libmenu/Makefile
libmenu/libmate-menu.pc
libmenu/libmate-menu-uninstalled.pc
layout/Makefile
desktop-directories/Makefile
util/Makefile
po/Makefile.in
])

dnl ---------------------------------------------------------------------------
dnl - Show summary
dnl ---------------------------------------------------------------------------

echo "
              mate-menus $VERSION
              `echo mate-menus $VERSION | sed "s/./=/g"`

        prefix:                       ${prefix}
        exec_prefix:                  ${exec_prefix}
        libdir:                       ${libdir}
        bindir:                       ${bindir}
        sbindir:                      ${sbindir}
        sysconfdir:                   ${sysconfdir}
        localstatedir:                ${localstatedir}
        datadir:                      ${datadir}
        source code location:         ${srcdir}
        compiler:                     ${CC}
        cflags:                       ${CFLAGS}
        Warning flags:                ${WARN_CFLAGS}
        Maintainer mode:              ${USE_MAINTAINER_MODE}
        Use *_DISABLE_DEPRECATED:     ${enable_deprecation_flags}

        Turn on debugging:            ${ax_enable_debug}
        Collection menu entry:        ${enable_collection}
        Build introspection support:  ${found_introspection}
        Native Language support:      ${USE_NLS}

"
