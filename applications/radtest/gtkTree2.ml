(* $Id: gtkTree2.ml,v 1.9 2002/05/30 05:49:10 garrigue Exp $ *)

open Gaux
open Gtk
open Tags
open GtkBase

module TreeItem = struct
  let cast w : tree_item obj =
    if Object.is_a w "GtkTreeItem" then Obj.magic w
    else invalid_arg "Gtk.TreeItem.cast"
  external create : unit -> tree_item obj = "ml_gtk_tree_item2_new"
  external create_with_label : string -> tree_item obj
      = "ml_gtk_tree_item2_new_with_label"
  let create ?label () =
    match label with None -> create ()
    | Some label -> create_with_label label
  external set_subtree : [>`treeitem] obj -> [>`widget] obj -> unit
      = "ml_gtk_tree_item2_set_subtree"
  external remove_subtree : [>`treeitem] obj -> unit
      = "ml_gtk_tree_item2_remove_subtree"
  external expand : [>`treeitem] obj -> unit
      = "ml_gtk_tree_item2_expand"
  external collapse : [>`treeitem] obj -> unit
      = "ml_gtk_tree_item2_collapse"
  external subtree : [>`treeitem] obj -> tree obj
      = "ml_GTK_TREE_ITEM2_SUBTREE"
  let subtree t = try subtree t with Gpointer.Null -> raise Not_found
  module Signals = struct
    open GtkSignal
    let expand =
      { name = "expand"; classe = `treeitem; marshaller = marshal_unit }
    let collapse =
      { name = "collapse"; classe = `treeitem; marshaller = marshal_unit }
  end
end

module Tree = struct
  let cast w : tree obj =
    if Object.is_a w "GtkTree" then Obj.magic w
    else invalid_arg "Gtk.Tree.cast"
  external coerce : [>`tree] obj -> tree obj = "%identity"
  external create : unit -> tree obj = "ml_gtk_tree2_new"
  external insert : [>`tree] obj -> [>`treeitem] obj -> pos:int -> unit
      = "ml_gtk_tree2_insert"
  external remove_items : [>`tree] obj -> [>`treeitem] obj list -> unit
      = "ml_gtk_tree2_remove_items"
  external clear_items : [>`tree] obj -> start:int -> stop:int -> unit
      = "ml_gtk_tree2_clear_items"
  external select_item : [>`tree] obj -> pos:int -> unit
      = "ml_gtk_tree2_select_item"
  external unselect_item : [>`tree] obj -> pos:int -> unit
      = "ml_gtk_tree2_unselect_item"
  external child_position : [>`tree] obj -> [>`treeitem] obj -> int
      = "ml_gtk_tree2_child_position"
(*  external set_selection_mode : [>`tree] obj -> selection_mode -> unit
      = "ml_gtk_tree2_set_selection_mode"
  external set_view_mode : [>`tree] obj -> [`LINE|`ITEM] -> unit
      = "ml_gtk_tree2_set_view_mode"
*)
  external set_view_lines : [>`tree] obj -> bool -> unit
      = "ml_gtk_tree2_set_view_lines"
  external selection : [>`tree] obj -> tree_item obj list =
    "ml_gtk_tree2_selection"
  external item_up : [>`tree] obj -> int -> unit =
    "ml_gtk_tree2_item_up"

  let set ?selection_mode ?view_mode ?view_lines w =
    let may_set f = may ~f:(f w) in
(*    may_set set_selection_mode selection_mode;
    may_set set_view_mode view_mode; *)
    may_set set_view_lines view_lines
  module Signals = struct
    open GtkSignal
    let selection_changed =
      { name = "selection_changed"; classe = `tree; marshaller = marshal_unit }
    let select_child =
      { name = "select_child"; classe = `tree;
        marshaller = Widget.Signals.marshal }
    let unselect_child =
      { name = "unselect_child"; classe = `tree;
        marshaller = Widget.Signals.marshal }
  end
end
