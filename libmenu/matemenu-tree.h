/*
 * Copyright (C) 2004 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __MATEMENU_TREE_H__
#define __MATEMENU_TREE_H__

#ifndef MATEMENU_I_KNOW_THIS_IS_UNSTABLE
#error "libmate-menu should only be used if you understand that it's subject to frequent change, and is not supported as a fixed API/ABI or as part of the platform"
#endif

#include <gio/gdesktopappinfo.h>

G_BEGIN_DECLS

#define MATEMENU_TYPE_TREE         (matemenu_tree_get_type ())
#define MATEMENU_TREE(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), MATEMENU_TYPE_TREE, MateMenuTree))
#define MATEMENU_TREE_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), MATEMENU_TYPE_TREE, MateMenuTreeClass))
#define MATEMENU_IS_TREE(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), MATEMENU_TYPE_TREE))
#define MATEMENU_IS_TREE_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), MATEMENU_TYPE_TREE))
#define MATEMENU_TREE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DESKTOP_APP_INFO, MateMenuTreeClass))

typedef struct _MateMenuTree        MateMenuTree;
typedef struct _MateMenuTreeClass   MateMenuTreeClass;

struct _MateMenuTreeClass
{
  GObjectClass parent_class;
};

GType matemenu_tree_get_type (void) G_GNUC_CONST;

typedef struct MateMenuTreeIter      MateMenuTreeIter;
typedef struct MateMenuTreeDirectory MateMenuTreeDirectory;
typedef struct MateMenuTreeEntry     MateMenuTreeEntry;
typedef struct MateMenuTreeSeparator MateMenuTreeSeparator;
typedef struct MateMenuTreeHeader    MateMenuTreeHeader;
typedef struct MateMenuTreeAlias     MateMenuTreeAlias;

typedef enum
{
  MATEMENU_TREE_ITEM_INVALID = 0,
  MATEMENU_TREE_ITEM_DIRECTORY,
  MATEMENU_TREE_ITEM_ENTRY,
  MATEMENU_TREE_ITEM_SEPARATOR,
  MATEMENU_TREE_ITEM_HEADER,
  MATEMENU_TREE_ITEM_ALIAS
} MateMenuTreeItemType;

GType matemenu_tree_iter_get_type (void);

/* Explicitly skip item, it's a "hidden" base class */
GType matemenu_tree_directory_get_type (void);
GType matemenu_tree_entry_get_type (void);
GType matemenu_tree_separator_get_type (void);
GType matemenu_tree_header_get_type (void);
GType matemenu_tree_alias_get_type (void);

typedef enum
{
  MATEMENU_TREE_FLAGS_NONE                = 0,
  MATEMENU_TREE_FLAGS_INCLUDE_EXCLUDED    = 1 << 0,
  MATEMENU_TREE_FLAGS_INCLUDE_NODISPLAY   = 1 << 1,
  MATEMENU_TREE_FLAGS_INCLUDE_UNALLOCATED = 1 << 2,
  /* leave some space for more include flags */
  MATEMENU_TREE_FLAGS_SHOW_EMPTY          = 1 << 8,
  MATEMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS = 1 << 9,
  /* leave some space for more show flags */
  MATEMENU_TREE_FLAGS_SORT_DISPLAY_NAME   = 1 << 16
} MateMenuTreeFlags;
GType matemenu_tree_flags_get_type (void);
#define MATEMENU_TYPE_TREE_FLAGS (matemenu_tree_flags_get_type ())

MateMenuTree *matemenu_tree_new (const char     *menu_basename,
                           MateMenuTreeFlags  flags);

MateMenuTree *matemenu_tree_new_for_path (const char     *menu_path,
                                    MateMenuTreeFlags  flags);

gboolean   matemenu_tree_load_sync (MateMenuTree  *tree,
                                 GError    **error);

const char         *matemenu_tree_get_canonical_menu_path (MateMenuTree  *tree);
MateMenuTreeDirectory *matemenu_tree_get_root_directory      (MateMenuTree  *tree);
MateMenuTreeDirectory *matemenu_tree_get_directory_from_path (MateMenuTree  *tree,
							const char *path);
MateMenuTreeEntry     *matemenu_tree_get_entry_by_id         (MateMenuTree  *tree,
							const char *id);

gpointer matemenu_tree_item_ref   (gpointer item);
void     matemenu_tree_item_unref (gpointer item);

MateMenuTreeDirectory *matemenu_tree_directory_get_parent    (MateMenuTreeDirectory *directory);
const char *matemenu_tree_directory_get_name              (MateMenuTreeDirectory *directory);
const char *matemenu_tree_directory_get_generic_name      (MateMenuTreeDirectory *directory);
const char *matemenu_tree_directory_get_comment           (MateMenuTreeDirectory *directory);
GIcon      *matemenu_tree_directory_get_icon              (MateMenuTreeDirectory *directory);
const char *matemenu_tree_directory_get_desktop_file_path (MateMenuTreeDirectory *directory);
const char *matemenu_tree_directory_get_menu_id           (MateMenuTreeDirectory *directory);
MateMenuTree  *matemenu_tree_directory_get_tree              (MateMenuTreeDirectory *directory);

gboolean matemenu_tree_directory_get_is_nodisplay (MateMenuTreeDirectory *directory);

MateMenuTreeIter      *matemenu_tree_directory_iter            (MateMenuTreeDirectory *directory);

MateMenuTreeIter      *matemenu_tree_iter_ref                  (MateMenuTreeIter *iter);
void                matemenu_tree_iter_unref                (MateMenuTreeIter *iter);

MateMenuTreeItemType   matemenu_tree_iter_next                 (MateMenuTreeIter *iter);
MateMenuTreeDirectory *matemenu_tree_iter_get_directory        (MateMenuTreeIter *iter);
MateMenuTreeEntry     *matemenu_tree_iter_get_entry            (MateMenuTreeIter *iter);
MateMenuTreeHeader    *matemenu_tree_iter_get_header           (MateMenuTreeIter *iter);
MateMenuTreeAlias     *matemenu_tree_iter_get_alias            (MateMenuTreeIter *iter);
MateMenuTreeSeparator *matemenu_tree_iter_get_separator        (MateMenuTreeIter *iter);

char *matemenu_tree_directory_make_path (MateMenuTreeDirectory *directory,
				      MateMenuTreeEntry     *entry);


GDesktopAppInfo    *matemenu_tree_entry_get_app_info       (MateMenuTreeEntry *entry);
MateMenuTreeDirectory *matemenu_tree_entry_get_parent         (MateMenuTreeEntry *entry);
MateMenuTree          *matemenu_tree_entry_get_tree           (MateMenuTreeEntry *entry);

const char *matemenu_tree_entry_get_desktop_file_path (MateMenuTreeEntry *entry);
const char *matemenu_tree_entry_get_desktop_file_id   (MateMenuTreeEntry *entry);

gboolean matemenu_tree_entry_get_is_nodisplay_recurse  (MateMenuTreeEntry *entry);
gboolean matemenu_tree_entry_get_is_excluded  (MateMenuTreeEntry *entry);
gboolean matemenu_tree_entry_get_is_unallocated  (MateMenuTreeEntry *entry);

MateMenuTreeDirectory *matemenu_tree_header_get_directory (MateMenuTreeHeader *header);
MateMenuTree          *matemenu_tree_header_get_tree      (MateMenuTreeHeader *header);
MateMenuTreeDirectory *matemenu_tree_header_get_parent    (MateMenuTreeHeader *header);

MateMenuTreeDirectory *matemenu_tree_alias_get_directory         (MateMenuTreeAlias *alias);
MateMenuTreeItemType   matemenu_tree_alias_get_aliased_item_type (MateMenuTreeAlias *alias);
MateMenuTreeDirectory *matemenu_tree_alias_get_aliased_directory (MateMenuTreeAlias *alias);
MateMenuTreeEntry     *matemenu_tree_alias_get_aliased_entry     (MateMenuTreeAlias *alias);
MateMenuTree          *matemenu_tree_alias_get_tree              (MateMenuTreeAlias *alias);
MateMenuTreeDirectory *matemenu_tree_alias_get_parent            (MateMenuTreeAlias *alias);

MateMenuTree          *matemenu_tree_separator_get_tree (MateMenuTreeSeparator *separator);
MateMenuTreeDirectory *matemenu_tree_separator_get_parent (MateMenuTreeSeparator *separator);

G_END_DECLS

#endif /* __MATEMENU_TREE_H__ */
