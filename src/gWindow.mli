(* $Id: gWindow.mli,v 1.52 2004/07/05 10:05:47 oandrieu Exp $ *)

open Gtk
open GObj

(** Windows *)

(** {3 GtkWindow} *)

(** @gtkdoc gtk GtkWindow *)
class window_skel : 'a obj ->
  object
    inherit GContainer.bin
    constraint 'a = [> Gtk.window]
    val obj : 'a obj
    method activate_default : unit -> bool
    method activate_focus : unit -> bool
    method add_accel_group : accel_group -> unit
    method as_window : Gtk.window obj
    method event : event_ops
    method deiconify : unit -> unit
    method iconify : unit -> unit
    method move : x:int -> y:int -> unit
    method parse_geometry : string -> bool
    method present : unit -> unit
    method resize : width:int -> height:int -> unit
    method show : unit -> unit
    method set_allow_grow : bool -> unit
    method set_allow_shrink : bool -> unit
    method set_default_height : int -> unit
    method set_default_size : width:int -> height:int -> unit
    method set_default_width : int -> unit
    method set_destroy_with_parent : bool -> unit
    method set_geometry_hints :
      ?min_size:int * int ->
      ?max_size:int * int ->
      ?base_size:int * int ->
      ?aspect:float * float ->
      ?resize_inc:int * int ->
      ?win_gravity:Gdk.Tags.gravity ->
      ?pos:bool -> ?user_pos:bool -> ?user_size:bool -> GObj.widget -> unit
    method set_gravity : Gdk.Tags.gravity -> unit
    method set_icon : GdkPixbuf.pixbuf option -> unit
    method set_modal : bool -> unit
    method set_position : Tags.window_position -> unit
    method set_resizable : bool -> unit
    method set_screen : Gdk.screen -> unit
    method set_skip_pager_hint : bool -> unit
    method set_skip_taskbar_hint : bool -> unit
    method set_title : string -> unit
    method set_transient_for : Gtk.window obj -> unit
    method set_type_hint : Gdk.Tags.window_type_hint -> unit
    method set_wm_class : string -> unit
    method set_wm_name : string -> unit
    method allow_grow : bool
    method allow_shrink : bool
    method default_height : int
    method default_width : int
    method destroy_with_parent : bool
    method has_toplevel_focus : bool
    method icon : GdkPixbuf.pixbuf option
    method is_active : bool
    method kind : Tags.window_type
    method modal : bool
    method position : Tags.window_position
    method resizable : bool
    method screen : Gdk.screen
    method skip_pager_hint : bool
    method skip_taskbar_hint : bool
    method title : string
    method type_hint : Gdk.Tags.window_type_hint
  end

(** Toplevel widget which can contain other widgets
   @gtkdoc gtk GtkWindow *)
class window : ([> Gtk.window] as 'a) obj ->
  object
    inherit window_skel
    val obj : 'a obj
    method connect : GContainer.container_signals
    method fullscreen : unit -> unit (** @since GTK 2.2 *)
    method maximize : unit -> unit
    method stick : unit -> unit
    method unfullscreen : unit -> unit (** @since GTK 2.2 *)
    method unmaximize : unit -> unit
    method unstick : unit -> unit
  end

(** @gtkdoc gtk GtkWindow *)
val window :
  ?kind:Tags.window_type ->
  ?title:string ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> window
(** @param kind default value is [`TOPLEVEL]
    @param allow_grow default value is [true]
    @param allow_shrink default value is [false]
    @param modal default value is [false]
    @param resizable default value is [true]
    @param type_hint default value is [`NORMAL]
    @param position default value is [`NONE] *)

val toplevel : #widget -> window option
(** return the toplevel window of this widget, if existing *)

(** {3 GtkDialog} *)

(** @gtkdoc gtk GtkDialog *)
class ['a] dialog_signals :
  ([> Gtk.dialog] as 'b) obj -> decode:(int -> 'a) ->
  object
    inherit GContainer.container_signals
    val obj : 'b obj
    method response : callback:('a -> unit) -> GtkSignal.id
    method close : callback:(unit -> unit) -> GtkSignal.id
  end

(** @gtkdoc gtk GtkDialog *)
class ['a] dialog_skel : ([>Gtk.dialog] as 'b) obj ->
  object
    constraint 'a = [> `DELETE_EVENT]
    inherit window_skel
    val obj : 'b obj
    method action_area : GPack.button_box
    method event : event_ops
    method vbox : GPack.box
    method response : 'a -> unit
    method set_response_sensitive : 'a -> bool -> unit
    method set_default_response : 'a -> unit
    method has_separator : bool
    method set_has_separator : bool -> unit
    method run : unit -> 'a
    method private encode : 'a -> int
    method private decode : int -> 'a
  end

(** Create popup windows
   @gtkdoc gtk GtkDialog *)
class ['a] dialog_ext : [> Gtk.dialog] obj ->
  object
    inherit ['a] dialog_skel
    method add_button : string -> 'a -> unit
    method add_button_stock : GtkStock.id -> 'a -> unit
  end

(** Create popup windows
   @gtkdoc gtk GtkDialog *)
class ['a] dialog : [> Gtk.dialog] obj ->
  object
    inherit ['a] dialog_ext
    method connect : 'a dialog_signals
  end

(** @gtkdoc gtk GtkDialog *)
val dialog :
  ?no_separator:bool ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?title:string ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> 'a dialog
(** @param no_separator default value is [false]
    @param destroy_with_parent default value is [false] *)

(** Variation for safe typing *)
type any_response = [GtkEnums.response | `OTHER of int]
class dialog_any : [> Gtk.dialog] obj -> [any_response] dialog


(** {3 GtkMessageDialog} *)

type 'a buttons
module Buttons : sig
  val ok : [>`OK] buttons
  val close : [>`CLOSE] buttons
  val yes_no : [>`YES|`NO] buttons
  val ok_cancel : [>`OK|`CANCEL] buttons
  type color_selection = [`OK | `CANCEL | `HELP | `DELETE_EVENT]
  type file_selection = [`OK | `CANCEL | `HELP | `DELETE_EVENT]
  type font_selection = [`OK | `CANCEL | `APPLY | `DELETE_EVENT]
end

(** Convenient message window
   @gtkdoc gtk GtkMessageDialog *)
class type ['a] message_dialog =
  object
    inherit ['a] dialog_skel
    val obj : [> Gtk.message_dialog] obj
    method connect : 'a dialog_signals
    method message_type : Tags.message_type
    method set_message_type : Tags.message_type -> unit
  end

(** @gtkdoc gtk GtkMessageDialog *)
val message_dialog :
  ?message:string ->
  message_type:Tags.message_type ->
  buttons:'a buttons ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?title:string ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> 'a message_dialog

(** {3 File Chooser Dialog} *)

(** @since GTK 2.4
    @gtkdoc gtk GtkFileChooserDialog *)
class ['a] file_chooser_dialog_signals :
 ([> Gtk.file_chooser|Gtk.dialog] as 'b) Gtk.obj -> decode:(int -> 'a) ->
   object
     inherit ['a] dialog_signals
     inherit GFile.chooser_signals
     val obj : 'b Gtk.obj
   end

(** @since GTK 2.4
    @gtkdoc gtk GtkFileChooserDialog *)
class ['a] file_chooser_dialog :
 ([> Gtk.file_chooser|Gtk.dialog] as 'b) Gtk.obj -> 
 object
   inherit ['a] dialog_ext
   inherit GFile.chooser
   val obj : 'b Gtk.obj
   method connect : 'a file_chooser_dialog_signals

   (** The following methods should be used to add the [OPEN] or
      [SAVE] button of a FileChooserDialog *)
   method add_select_button : string -> 'a -> unit

   (** ditto with a stock id *)
   method add_select_button_stock : GtkStock.id -> 'a -> unit
 end

(** @since GTK 2.4
    @gtkdoc gtk GtkFileChooserDialog *)
val file_chooser_dialog :
  action:GtkEnums.file_chooser_action ->
  ?backend:string ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?title:string ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> 'a file_chooser_dialog
  


(** {3 Selection Dialogs} *)

(** @gtkdoc gtk GtkColorSelectionDialog *)
class color_selection_dialog : Gtk.color_selection_dialog obj ->
  object
    inherit [Buttons.color_selection] dialog_skel
    val obj : Gtk.color_selection_dialog obj
    method connect : Buttons.color_selection dialog_signals
    method cancel_button : GButton.button
    method colorsel : GMisc.color_selection
    method help_button : GButton.button
    method ok_button : GButton.button
  end

(** @gtkdoc gtk GtkColorSelectionDialog *)
val color_selection_dialog :
  ?title:string ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> color_selection_dialog


(** @gtkdoc gtk GtkFileSelection *)
class file_selection : Gtk.file_selection obj ->
  object
    inherit [Buttons.file_selection] dialog_skel
    val obj : Gtk.file_selection obj
    method connect : Buttons.file_selection dialog_signals
    method cancel_button : GButton.button
    method complete : filter:string -> unit
    method filename : string
    method get_selections : string list
    method help_button : GButton.button
    method ok_button : GButton.button
    method file_list : string GList.clist
    method dir_list : string GList.clist	
    method select_multiple : bool
    method show_fileops : bool
    method set_filename : string -> unit
    method set_show_fileops : bool -> unit
    method set_select_multiple : bool -> unit
  end

(** @gtkdoc gtk GtkFileSelection *)
val file_selection :
  ?title:string ->
  ?show_fileops:bool ->
  ?filename:string ->
  ?select_multiple:bool ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> file_selection

(** @gtkdoc gtk GtkFontSelectionDialog*)
class font_selection_dialog : Gtk.font_selection_dialog obj ->
  object
    inherit [Buttons.font_selection] dialog_skel
    val obj : Gtk.font_selection_dialog obj
    method connect : Buttons.font_selection dialog_signals
    method apply_button : GButton.button
    method cancel_button : GButton.button
    method selection : GMisc.font_selection
    method ok_button : GButton.button
  end

(** @gtkdoc gtk GtkFontSelectionDialog*)
val font_selection_dialog :
  ?title:string ->
  ?parent:#window_skel ->
  ?destroy_with_parent:bool ->
  ?allow_grow:bool ->
  ?allow_shrink:bool ->
  ?icon:GdkPixbuf.pixbuf ->
  ?modal:bool ->
  ?resizable:bool ->
  ?screen:Gdk.screen ->
  ?type_hint:Gdk.Tags.window_type_hint ->
  ?position:Tags.window_position ->
  ?wm_name:string ->
  ?wm_class:string ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> font_selection_dialog

(** {3 GtkPlug} *)

(** @gtkdoc gtk GtkPlug *)
class plug_signals : ([> Gtk.plug] as 'a) obj ->
  object
    inherit GContainer.container_signals
    val obj : 'a obj
    method embedded : callback:(unit -> unit) -> GtkSignal.id
  end

(** Toplevel for embedding into other processes 
   @gtkdoc gtk GtkPlug *)
class plug : Gtk.plug obj ->
  object
    inherit window_skel
    val obj : Gtk.plug obj
    method connect : plug_signals
  end

(** @gtkdoc gtk GtkPlug *)
val plug :
  window:Gdk.xid ->
  ?border_width:int ->
  ?width:int -> ?height:int -> ?show:bool -> unit -> plug

(** {3 GtkSocket} *)

(** @gtkdoc gtk GtkSocket *)
class socket_signals : ([>Gtk.socket] as 'a) obj ->
  object
    inherit GContainer.container_signals
    val obj : 'a obj
    method plug_added : callback:(unit -> unit) -> GtkSignal.id
    method plug_removed : callback:(unit -> unit) -> GtkSignal.id
  end

(** Container for widgets from other processes
   @gtkdoc gtk GtkSocket *)
class socket : Gtk.socket obj ->
  object
    inherit GContainer.container
    val obj : Gtk.socket obj
    method connect : socket_signals
    method steal : Gdk.xid -> unit
    (** @deprecated "inherently unreliable" *)
    method xwindow : Gdk.xid
  end

(** @gtkdoc gtk GtkSocket *)
val socket :
  ?border_width:int -> ?width:int -> ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> socket
