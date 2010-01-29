BUILT_SOURCES = vala.stamp

AM_CPPFLAGS = $(PROGRAM_CFLAGS)

bin_PROGRAMS = omap-terminal

omap_terminal_VALASOURCES = \
	omap-terminal.gs

omap_terminal_SOURCES = \
	$(omap_terminal_VALASOURCES:.gs=.c)

vala.stamp: $(omap_terminal_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap_terminal_LDADD = \
	$(PROGRAM_LIBS)

desktopdir = $(datadir)/applications
desktop_DATA = omap-terminal.desktop

EXTRA_DIST = \
	$(omap_terminal_VALASOURCES) \
	vala.stamp \
	omap-terminal.desktop

