noinst_PROGRAMS = mate-menu-spec-test

AM_CPPFLAGS = \
	$(GIO_UNIX_CFLAGS)					\
	-I$(srcdir)/../libmenu \
	-DMATEMENU_I_KNOW_THIS_IS_UNSTABLE \
	-DMATELOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(DISABLE_DEPRECATED_CFLAGS) \
	$(DEBUG_CFLAGS)

AM_CFLAGS = $(WARN_CFLAGS)

mate_menu_spec_test_SOURCES = \
	test-menu-spec.c

mate_menu_spec_test_LDADD = \
	$(GIO_UNIX_LIBS)		\
	../libmenu/libmate-menu.la

exampledir = $(pkgdatadir)/examples
example_DATA = mate-menus-ls.py

EXTRA_DIST = $(example_DATA)

-include $(top_srcdir)/git.mk

