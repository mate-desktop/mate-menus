t = executable('mate-menu-spec-test',
  sources : 'test-menu-spec.c',
  dependencies : libmate_menu_deps,
  install : false,
)

test('mate-menu-testing', t)

install_data('mate-menus-ls.py', install_dir : pkgdatadir / 'examples')

