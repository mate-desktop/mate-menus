directorydir = $(datadir)/mate/desktop-directories

# Should be moved to mate-control-center:
directory_in_controlcenterfiles = \
	mate-hardware.directory.in \
	mate-internet-and-network.directory.in \
	mate-look-and-feel.directory.in \
	mate-personal.directory.in \
	mate-system.directory.in

directory_in_files = \
	mate-audio-video.directory.in \
	mate-development.directory.in \
	mate-education.directory.in \
	mate-game.directory.in \
	mate-graphics.directory.in \
	mate-network.directory.in \
	mate-office.directory.in \
	mate-settings.directory.in \
	mate-settings-system.directory.in \
	mate-system-tools.directory.in \
	mate-utility.directory.in \
	mate-utility-accessibility.directory.in \
	mate-other.directory.in \
	mate-menu-applications.directory.in \
	mate-menu-system.directory.in \
	mate-collection.directory.in \
	$(directory_in_controlcenterfiles)

directory_DATA = $(directory_in_files:.directory.in=.directory)

%.directory: %.directory.in
if USE_NLS
	$(AM_V_GEN) $(MSGFMT) --desktop --keyword= --keyword=Name --keyword=Description --template $< -d $(top_srcdir)/po -o $@
else
	$(AM_V_GEN) cp $< $@
endif

EXTRA_DIST= $(directory_in_files)

CLEANFILES = $(directory_DATA)

-include $(top_srcdir)/git.mk
