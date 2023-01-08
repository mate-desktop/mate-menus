source_h = [
  'matemenu-tree.h',
]

install_headers(source_h, subdir : 'mate-menus')

sources = [
  'desktop-entries.h',
  'entry-directories.h',
  'menu-layout.h',
  'menu-monitor.h',
  'menu-util.h',
  'desktop-entries.c',
  'entry-directories.c',
  'matemenu-tree.c',
  'menu-layout.c',
  'menu-monitor.c',
  'menu-util.c',
]

gnome = import('gnome')
pkg = import('pkgconfig')

libmate_menu = shared_library('mate-menu',
  sources,
  dependencies: [gio_unix_dep],
  soversion: soversion,
  version: libversion,
  include_directories: top_srcdir,
  install : true,
  install_dir : get_option('libdir')
  )

libmate_menu_deps = declare_dependency(sources: source_h,
                                include_directories: [top_srcdir, include_directories('.')],
                                dependencies: [gio_unix_dep],
                                link_with: libmate_menu)

pkg.generate(
  name: 'mate-menu',
  version: meson.project_version(),
  description: 'Desktop Menu Specification Implementation',
  requires_private: 'gio-unix-2.0',
  filebase: 'libmate-menu',
  libraries: '-lmate-menu',
  subdirs: 'mate-menus',
  )

if get_option('introspection')
  libmate_menu_gir = gnome.generate_gir(libmate_menu,
    sources: [source_h, sources],
    nsversion : api_version,
    namespace : 'MateMenu',
    symbol_prefix : 'matemenu',
    export_packages: 'libmatemenu',
    identifier_prefix : 'MateMenu',
    link_with: libmate_menu,
    includes : ['Gio-2.0'],
    install : true,
    install_dir_gir: girdir,
    install_dir_typelib: typelibdir,
    extra_args: [ '--c-include=mate-menus/matemenu-tree.h' ],
    )
  if get_option('vapi')
    mate_menu_vapi = gnome.generate_vapi('libmate-menu',
      sources: libmate_menu_gir.get(0),
      packages: 'gio-unix-2.0',
      install: true,
      install_dir: vapidir,
      )
  endif
endif
