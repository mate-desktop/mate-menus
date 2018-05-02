# vim: set ts=4 sw=4 et:

#
# Copyright (C) 2008 Novell, Inc.
#
# Authors: Vincent Untz <vuntz@gnome.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
# MA  02110-1301, USA.
#

import optparse
import sys
import gi
gi.require_version('MateMenu', '2.0')
from gi.repository import MateMenu

def print_directory(dir, parent_path = None):
    if not parent_path:
        path = '/'
    else:
        path = '%s%s/' % (parent_path, dir.get_name())

    iter = dir.iter()
    nextType = iter.next()
    while(nextType != MateMenu.TreeItemType.INVALID):
        if (nextType == MateMenu.TreeItemType.ENTRY):
            entry = iter.get_entry()
            print(path + "\t" + entry.get_app_info().get_name() + "\t" + entry.get_desktop_file_path())
        elif (nextType == MateMenu.TreeItemType.DIRECTORY):
            print_directory(iter.get_directory(), path);
        nextType = iter.next()

def main(args):
    parser = optparse.OptionParser()

    parser.add_option('-f', '--file', dest='file',
                      help='Menu file')
    parser.add_option('-i', '--include-excluded', dest='exclude',
                      action='store_true', default=False,
                      help='Include <Exclude>d entries')
    parser.add_option('-n', '--include-nodisplay', dest='nodisplay',
                      action='store_true', default=False,
                      help='Include NoDisplay=true entries')

    (options, args) = parser.parse_args()

    if options.file:
        menu_file = options.file
    else:
        menu_file = 'mate-applications.menu'

    flags = MateMenu.TreeFlags.NONE
    if options.exclude:
        flags |= MateMenu.TreeFlags.INCLUDE_EXCLUDED
    if options.nodisplay:
        flags |= MateMenu.TreeFlags.INCLUDE_NODISPLAY
    tree = MateMenu.Tree(menu_basename = "mate-applications.menu", flags = flags)
    tree.load_sync();
    root = tree.get_root_directory()

    if not root:
        print('Menu tree is empty')
    else:
        print_directory(root)

if __name__ == '__main__':
    try:
      main(sys.argv)
    except KeyboardInterrupt:
      pass
