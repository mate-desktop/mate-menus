project(
  'mate-menus', 'c',
  version: '1.28.0',
  meson_version: '>=0.56.0',
  license: 'GPL2',
  default_options : [ 'warning_level=1', 'buildtype=debugoptimized', 'c_std=gnu11'],
)

package_name = meson.project_name()
package_version = meson.project_version()

# Versionning
version_arr = package_version.split('.')
mate_menu_version_major = version_arr[0].to_int()
mate_menu_version_minor = version_arr[1].to_int()
mate_menu_version_micro = version_arr[2].to_int()

api_version = '2.0'
soversion = 2

if mate_menu_version_minor.is_odd()
  mate_menu_interface_age = 0
else
  mate_menu_interface_age = mate_menu_version_micro
endif

# maintaining compatibility with the previous libtool versioning
# current = minor * 100 + micro - interface
# revision = interface
current = mate_menu_version_minor * 100 + mate_menu_version_micro - mate_menu_interface_age
revision = mate_menu_interface_age
libversion = '@0@.@1@.@2@'.format(soversion, current, revision)
# FIXME: next version should use above code for libversion
libversion = '2.4.9'

package_string = '@0@ @1@.0'.format(package_name, package_version)

config_h = configuration_data()
config_h.set_quoted('PACKAGE', package_name, description: 'Name of package')
config_h.set_quoted('PACKAGE_NAME', package_name, description: 'Define to the full name of this package.')
config_h.set_quoted('PACKAGE_STRING', package_string, description: 'Define to the full name and version of this package.')
config_h.set_quoted('PACKAGE_VERSION', package_version, description: 'Define to the version of this package.')
config_h.set_quoted('PACKAGE_URL', 'https://mate-desktop.org', description: 'Define to the home page for this package.')
config_h.set_quoted('GETTEXT_PACKAGE', package_name, description: 'Gettext package')
config_h.set_quoted('VERSION', package_version, description: 'Name of package')

if get_option('collection')
  config_h.set10('WITH_COLLECTION', true)
endif

# Compiler & Project arguments
add_project_arguments([
  '-DHAVE_CONFIG_H',
  '-DMATEMENU_I_KNOW_THIS_IS_UNSTABLE',
  '-I' + meson.project_build_root(),
  ], language: 'c')

# get suported warning flags
test_args = [
  '-fstack-protector-strong',
  '-Waggregate-return',
  '-Warray-bounds',
  '-Wcast-align',
  '-Wchar-subscripts',
  '-Wclobbered',
  '-Wdeclaration-after-statement',
  '-Wempty-body',
  '-Wformat=2',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Werror=format-security',
  '-Werror=format=2',
  '-Wformat-signedness',
  '-Wignored-qualifiers',
  '-Wimplicit-function-declaration',
  '-Winit-self',
  '-Winline',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-include-dirs',
  '-Wmissing-noreturn',
  '-Wmissing-parameter-type',
  '-Wmissing-prototypes',
  '-Wnested-externs',
  '-Wno-discarded-qualifiers',
  '-Wno-missing-field-initializers',
  '-Wno-strict-aliasing',
  '-Wno-suggest-attribute=format',
  '-Wno-unused-parameter',
  '-Wold-style-definition',
  '-Woverride-init',
  '-Wpacked',
  '-Wpointer-arith',
  '-Wredundant-decls',
  '-Wreturn-type',
  '-Wshadow',
  '-Wsign-compare',
  '-Wstrict-aliasing',
  '-Wstrict-prototypes',
  '-Wswitch-default',
  '-Wtype-limits',
  '-Wundef',
  '-Wuninitialized',
  '-Wunused-but-set-variable',
  '-Wwrite-strings',
  '-ansi',
  ]

cc = meson.get_compiler('c')

foreach arg: test_args
  if cc.has_multi_arguments(arg)
    add_project_arguments(arg, language : 'c')
  endif
endforeach

gnome = import('gnome')
i18n = import('i18n')

# Paths
top_srcdir = include_directories('.')
srcdir = meson.current_source_dir()
builddir = meson.current_build_dir()

prefix = get_option('prefix')
buildtype = get_option('buildtype')
bindir = join_paths(prefix, get_option('bindir'))
libdir = join_paths(prefix, get_option('libdir'))
datadir = join_paths(prefix, get_option('datadir'))
pkgdatadir = join_paths(datadir, package_name)

# Setup various paths that subdirectory meson.build files need
package_subdir = get_option('package_subdir')
girdir = join_paths(get_option('datadir'), package_subdir, 'gir-1.0')
typelibdir = join_paths(get_option('libdir'), package_subdir, 'girepository-1.0')
libdir = join_paths(get_option('libdir'), package_subdir)
if package_subdir != ''
  vapidir = join_paths(get_option('datadir'), package_subdir, 'vapi')
else
  vapidir = join_paths(get_option('datadir'), 'vala', 'vapi')
endif

if get_option('debug')
  add_project_arguments('-DG_ENABLE_DEBUG', language : 'c')
else
  add_project_arguments('-DG_DISABLE_ASSERT',
                        '-DG_DISABLE_CHECKS',
                        language : 'c')
endif

# Dependencies
gio_req = '>= 2.50.0'
gio_unix_dep = dependency('gio-unix-2.0', version: gio_req)

configure_file(
  output: 'config.h',
  configuration: config_h
)

subdir('libmenu')
subdir('layout')
subdir('desktop-directories')
subdir('util')
subdir('po')

summary({
  'prefix': prefix,
  'exec_prefix': get_option('bindir'),
  'libdir': libdir,
  'bindir': bindir,
  'sbindir': get_option('sbindir'),
  'sysconfdir': get_option('sysconfdir'),
  'localstatedir': get_option('localstatedir'),
  'datadir': datadir,
  },
  section: 'Directories'
)

summary({
  'Turn on debugging': get_option('debug'),
  'Collection menu entry': get_option('collection'),
  'Build introspection support': get_option('introspection'),
  },
  section: 'Configuration'
)
