(* $Id: gBin.mli,v 1.13 2003/09/27 13:42:19 oandrieu Exp $ *)

open Gtk
open GObj
open GContainer

(** Containers with just one child *)

(** {3  GtkScrolledWindow } *)

(** Adds scrollbars to its child widget
   @gtkdoc gtk GtkScrolledWindow  *)
class scrolled_window : Gtk.scrolled_window obj ->
  object
    inherit GContainer.container_full
    val obj : Gtk.scrolled_window obj
    method add_with_viewport : widget -> unit
    method set_hadjustment : GData.adjustment -> unit
    method set_hpolicy : Tags.policy_type -> unit
    method set_placement : Tags.corner_type -> unit
    method set_shadow_type : Tags.shadow_type -> unit
    method set_vadjustment : GData.adjustment -> unit
    method set_vpolicy : Tags.policy_type -> unit
    method hadjustment : GData.adjustment
    method shadow_type : Gtk.Tags.shadow_type
    method hpolicy : Tags.policy_type
    method placement : Tags.corner_type
    method vadjustment : GData.adjustment
    method vpolicy : Tags.policy_type
  end

(** @gtkdoc gtk GtkScrolledWindow  *)
val scrolled_window :
  ?hadjustment:GData.adjustment ->
  ?vadjustment:GData.adjustment ->
  ?hpolicy:Tags.policy_type ->
  ?vpolicy:Tags.policy_type ->
  ?placement:Tags.corner_type ->
  ?shadow_type:Gtk.Tags.shadow_type ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> scrolled_window

(** {3 GtkEventBox} *)

(** A widget used to catch events for widgets which do not have their own window
   @gtkdoc gtk GtkEventBox *)
class event_box : ([> Gtk.event_box] as 'a) obj ->
  object
    inherit GContainer.container_full
    val obj : 'a obj
    method event : event_ops
  end

(** @gtkdoc gtk GtkEventBox *)
val event_box :
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> event_box

(** {3 GtkHandleBox} *)

(** @gtkdoc gtk GtkHandleBox *)
class handle_box_signals : 'a obj ->
  object
    inherit GContainer.container_signals
    constraint 'a = [> handle_box]
    val obj : 'a obj
    method child_attached : callback:(widget -> unit) -> GtkSignal.id
    method child_detached : callback:(widget -> unit) -> GtkSignal.id
  end

(** A widget for detachable window portions
   @gtkdoc gtk GtkHandleBox *)
class handle_box : Gtk.handle_box obj ->
  object
    inherit GContainer.container
    val obj : Gtk.handle_box obj
    method event : event_ops
    method connect : handle_box_signals
    method set_handle_position : Tags.position -> unit
    method set_shadow_type : Tags.shadow_type -> unit
    method set_snap_edge : Tags.position -> unit
    method handle_position : Tags.position
    method shadow_type : Tags.shadow_type
    method snap_edge : Tags.position
  end

(** @gtkdoc gtk GtkHandleBox *)
val handle_box :
  ?handle_position:Tags.position ->
  ?snap_edge:Tags.position ->
  ?shadow_type:Tags.shadow_type ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> handle_box

(** {3 GtkFrame & GtkAspectFrame} *)

class frame_skel : 'a obj ->
  object
    inherit GContainer.container
    constraint 'a = [> frame]
    val obj : 'a obj
    method set_label : string option -> unit
    method set_label_widget : GObj.widget option -> unit
    method set_label_xalign : float -> unit
    method set_label_yalign : float -> unit
    method set_shadow_type : Tags.shadow_type -> unit
    method label : string option
    method label_widget : GObj.widget option
    method label_xalign : float
    method label_yalign : float
    method shadow_type : Tags.shadow_type
  end

(** A bin with a decorative frame and optional label
   @gtkdoc gtk GtkFrame *)
class frame : Gtk.frame obj ->
  object
    inherit frame_skel
    val obj : Gtk.frame obj
    method connect : GContainer.container_signals
  end

(** @gtkdoc gtk GtkFrame *)
val frame :
  ?label:string ->
  ?label_xalign:clampf ->
  ?label_yalign:clampf ->
  ?shadow_type:Tags.shadow_type ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> frame

(** A frame that constrains its child to a particular aspect ratio
   @gtkdoc gtk GtkAspectFrame *)
class aspect_frame : Gtk.aspect_frame obj ->
  object
    inherit frame
    val obj : Gtk.aspect_frame obj
    method set_obey_child : bool -> unit
    method set_ratio : float -> unit
    method set_xalign : float -> unit
    method set_yalign : float -> unit
    method obey_child : bool
    method ratio : float
    method xalign : float
    method yalign : float
  end

(** @gtkdoc gtk GtkAspectFrame *)
val aspect_frame :
  ?obey_child:bool ->
  ?ratio:float ->
  ?xalign:clampf ->
  ?yalign:clampf ->
  ?label:string ->
  ?label_xalign:clampf ->
  ?label_yalign:clampf ->
  ?shadow_type:Tags.shadow_type ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> aspect_frame

(** {3 GtkViewport} *)

(** @gtkdoc gtk GtkViewport *)
class viewport : Gtk.viewport obj ->
  object
    inherit GContainer.container_full
    val obj : Gtk.viewport obj
    method event : event_ops
    method set_hadjustment : GData.adjustment -> unit
    method set_shadow_type : Tags.shadow_type -> unit
    method set_vadjustment : GData.adjustment -> unit
    method hadjustment : GData.adjustment
    method shadow_type : Tags.shadow_type
    method vadjustment : GData.adjustment
  end

(** @gtkdoc gtk GtkViewport *)
val viewport :
  ?hadjustment:GData.adjustment ->
  ?vadjustment:GData.adjustment ->
  ?shadow_type:Tags.shadow_type ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> viewport

(** {3 GtkAlignment}
   A widget which controls the alignment and size of its child
   @gtkdoc gtk GtkAlignment *)
class alignment : Gtk.alignment obj ->
  object
    inherit GContainer.container_full
    val obj : Gtk.alignment obj
    method set_xalign : Gtk.clampf -> unit
    method set_yalign : Gtk.clampf -> unit
    method set_xscale : Gtk.clampf -> unit
    method set_yscale : Gtk.clampf -> unit
    method xalign : Gtk.clampf
    method yalign : Gtk.clampf
    method xscale : Gtk.clampf
    method yscale : Gtk.clampf
  end

(** @gtkdoc gtk GtkAlignment *)
val alignment :
  ?xalign:Gtk.clampf ->
  ?yalign:Gtk.clampf ->
  ?xscale:Gtk.clampf ->
  ?yscale:Gtk.clampf ->
  ?border_width:int ->
  ?width:int ->
  ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> alignment
val alignment_cast : #widget -> alignment

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
    method xwindow : Gdk.xid
  end

(** @gtkdoc gtk GtkSocket *)
val socket :
  ?border_width:int -> ?width:int -> ?height:int ->
  ?packing:(widget -> unit) -> ?show:bool -> unit -> socket
