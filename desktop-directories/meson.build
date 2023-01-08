desktop_files = [
# Should be moved to mate-control-center:
	'mate-hardware.directory',
	'mate-internet-and-network.directory',
	'mate-look-and-feel.directory',
	'mate-personal.directory',
	'mate-system.directory',

	'mate-audio-video.directory',
	'mate-development.directory',
	'mate-education.directory',
	'mate-game.directory',
	'mate-graphics.directory',
	'mate-network.directory',
	'mate-office.directory',
	'mate-settings.directory',
	'mate-settings-system.directory',
	'mate-system-tools.directory',
	'mate-utility.directory',
	'mate-utility-accessibility.directory',
	'mate-other.directory',
	'mate-menu-applications.directory',
	'mate-menu-system.directory',
	'mate-collection.directory',
]

foreach f : desktop_files
  desktop_file = i18n.merge_file(
    input: '@0@.in'.format(f),
    output: f,
    type: 'desktop',
    po_dir: join_paths(srcdir, 'po'),
    install: true,
    install_dir: join_paths(
      datadir,
      'mate',
      'desktop-directories',
    )
  )
endforeach
