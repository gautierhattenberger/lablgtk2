(* $Id: gContainer.mli,v 1.19 2003/09/27 13:42:19 oandrieu Exp $ *)

open Gtk
open GObj

(** Widgets which contain other widgets *)

class focus :
  'a obj ->
  object
    constraint 'a = [> `container]
    val obj : 'a obj
    (* method circulate : Tags.direction_type -> bool *)
    method set : widget option -> unit
    method set_hadjustment : GData.adjustment option -> unit
    method set_vadjustment : GData.adjustment option -> unit
  end

(** {3 GtkContainer} *)

(** Base class for widgets which contain other widgets
   @gtkdoc gtk GtkContainer *)
class container : ([> Gtk.container] as 'a) obj ->
  object
    inherit GObj.widget
    val obj : 'a obj
    method add : widget -> unit
    method children : widget list
    method remove : widget -> unit
    method focus : focus
    method set_border_width : int -> unit
    method set_resize_mode : Tags.resize_mode -> unit
    method border_width : int
    method resize_mode : Tags.resize_mode
  end

(** @gtkdoc gtk GtkContainer *)
class ['a] container_impl :([> Gtk.container] as 'a) obj ->
  object
    inherit container
    inherit ['a] GObj.objvar
  end

(** @gtkdoc gtk GtkContainer *)
class type container_signals =
  object
    inherit GObj.widget_signals
    method add : callback:(widget -> unit) -> GtkSignal.id
    method remove : callback:(widget -> unit) -> GtkSignal.id
  end

(** @gtkdoc gtk GtkContainer *)
class container_signals_impl : ([> Gtk.container] as 'a) obj ->
  object
    inherit ['a] GObj.gobject_signals
    inherit container_signals
  end

(** @gtkdoc gtk GtkContainer *)
class container_full : ([> Gtk.container] as 'a) obj ->
  object
    inherit container
    val obj : 'a obj
    method connect : container_signals
  end

(** @raise Gtk.Cannot_cast "GtkContainer" *)
val cast_container : widget -> container_full

(** @gtkdoc gtk GtkContainer *)
val pack_container :
  create:([> Gtk.container] Gobject.param list -> (#GObj.widget as 'a)) ->
  [> Gtk.container] Gobject.param list ->
  ?border_width:int ->
  ?width:int ->
  ?height:int -> ?packing:(GObj.widget -> unit) -> ?show:bool -> unit -> 'a

(** {3 GtkItem} *)

(** @gtkdoc gtk GtkContainer *)
class virtual ['a] item_container : ([> Gtk.container] as 'c) obj ->
  object
    constraint 'a = < as_item : [>`widget] obj; .. >
    inherit GObj.widget
    val obj : 'c obj
    method add : 'a -> unit
    method append : 'a -> unit
    method children : 'a list
    method virtual insert : 'a -> pos:int -> unit
    method prepend : 'a -> unit
    method remove : 'a -> unit
    method focus : focus
    method set_border_width : int -> unit
    method set_resize_mode : Tags.resize_mode -> unit
    method border_width : int
    method resize_mode : Tags.resize_mode
    method private virtual wrap : Gtk.widget obj -> 'a
  end

(** @gtkdoc gtk GtkItem *)
class item_signals : [> Gtk.item] obj ->
  object
    inherit container_signals
    method deselect : callback:(unit -> unit) -> GtkSignal.id
    method select : callback:(unit -> unit) -> GtkSignal.id
    method toggle : callback:(unit -> unit) -> GtkSignal.id
  end
