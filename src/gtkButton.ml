(* $Id: gtkButton.ml,v 1.22 2004/05/09 14:39:14 oandrieu Exp $ *)

open Gaux
open Gobject
open Gtk
open Tags
open GtkButtonProps
open GtkBase

external _gtkbutton_init : unit -> unit = "ml_gtkbutton_init"
let () = _gtkbutton_init ()

module Button = struct
  include Button
  let make_params ~cont p ?label ?use_mnemonic ?stock =
    let label, use_stock =
      match stock with None -> label, None
      | Some id -> Some (GtkStock.convert_id id), Some true in
    make_params ~cont p ?label ?use_underline:use_mnemonic ?use_stock
  external pressed : [>`button] obj -> unit = "ml_gtk_button_pressed"
  external released : [>`button] obj -> unit = "ml_gtk_button_released"
  external clicked : [>`button] obj -> unit = "ml_gtk_button_clicked"
  external enter : [>`button] obj -> unit = "ml_gtk_button_enter"
  external leave : [>`button] obj -> unit = "ml_gtk_button_leave"
end

module ToggleButton = struct
  include ToggleButton
  let create_check pl : toggle_button obj = Object.make "GtkCheckButton" pl
  external toggled : [>`toggle] obj -> unit
      = "ml_gtk_toggle_button_toggled"
end

module RadioButton = struct
  include RadioButton
  let create ?group p = create (Property.may_cons P.group group p)
end

module Toolbar = struct
  include Toolbar
  external insert_space : [>`toolbar] obj -> pos:int -> unit
      = "ml_gtk_toolbar_insert_space"
  let insert_space w ?(pos = -1) () = insert_space w ~pos
  external insert_button :
      [>`toolbar] obj -> kind:[`BUTTON|`TOGGLEBUTTON|`RADIOBUTTON] ->
      text:string -> tooltip:string ->
      tooltip_private:string ->
      icon:[>`widget] optobj -> pos:int -> button obj
      = "ml_gtk_toolbar_insert_element_bc" "ml_gtk_toolbar_insert_element"
  let insert_button w ?(kind=`BUTTON) ?(text="") ?(tooltip="")
      ?(tooltip_private="") ?icon ?(pos = -1) ?callback () =
    let b =insert_button w ~kind ~text ~tooltip ~tooltip_private ~pos
        ~icon:(Gpointer.optboxed icon)
    in
    may callback ~f:
      (fun callback -> GtkSignal.connect b ~sgn:Button.S.clicked ~callback);
    b
  external insert_widget :
      [>`toolbar] obj -> [>`widget] obj ->
      tooltip:string -> tooltip_private:string -> pos:int -> unit
      = "ml_gtk_toolbar_insert_widget"
  let insert_widget w ?(tooltip="") ?(tooltip_private="") ?(pos = -1) w' =
    insert_widget w w' ~tooltip ~tooltip_private ~pos
  external set_tooltips : [>`toolbar] obj -> bool -> unit =
    "ml_gtk_toolbar_set_tooltips"
  external get_tooltips : [>`toolbar] obj -> bool
      = "ml_gtk_toolbar_get_tooltips"
  let set ?orientation ?style ?tooltips w =
    may orientation ~f:(set P.orientation w);
    may style ~f:(set P.toolbar_style w);
    may tooltips ~f:(set_tooltips w)
  external unset_style : [>`toolbar] obj -> unit = "ml_gtk_toolbar_unset_style"
  external get_icon_size : [>`toolbar] obj -> Tags.icon_size
      = "ml_gtk_toolbar_get_icon_size"
  external set_icon_size : [>`toolbar] obj -> Tags.icon_size -> unit 
      = "ml_gtk_toolbar_set_icon_size"
  external unset_icon_size : [>`toolbar] obj -> unit 
      = "ml_gtk_toolbar_unset_icon_size"

  (* extended API in GTK 2.4 *)
  external insert : [>`toolbar] obj -> [>`toolitem] obj -> pos:int -> unit
      = "ml_gtk_toolbar_insert"
  external get_item_index : [>`toolbar] obj -> [>`toolitem] obj -> int
      = "ml_gtk_toolbar_get_item_index"
  external get_n_items : [>`toolbar] obj -> int = "ml_gtk_toolbar_get_n_items"
  external get_nth_item : [>`toolbar] obj -> int -> [`toolitem] obj
      = "ml_gtk_toolbar_get_nth_item"
  external get_drop_index : [>`toolbar] obj -> int -> int -> int
      = "ml_gtk_toolbar_get_drop_index"
  external set_drop_highlight_item : [>`toolbar] obj -> [>`toolitem] obj option -> int -> unit
      = "ml_gtk_toolbar_set_drop_highlight_item"
  external get_relief_style : [>`toolbar] obj -> GtkEnums.relief_style
      = "ml_gtk_toolbar_get_relief_style"
end

module ColorButton = ColorButton

module FontButton = FontButton

module ToolItem = ToolItem

module SeparatorToolItem = SeparatorToolItem

module ToolButton = ToolButton

module ToggleToolButton = ToggleToolButton

module RadioToolButton = RadioToolButton
