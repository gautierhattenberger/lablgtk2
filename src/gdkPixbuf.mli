(* $Id: gdkPixbuf.mli,v 1.6 2004/03/15 05:12:15 garrigue Exp $ *)

(* Types *)

type pixbuf = [`pixbuf] Gobject.obj
type colorspace = [ `RGB]
type alpha_mode = [ `BILEVEL | `FULL]
type interpolation = [ `BILINEAR | `HYPER | `NEAREST | `TILES]
type uint8 = int

type gdkpixbuferror =
  | ERROR_CORRUPT_IMAGE
  | ERROR_INSUFFICIENT_MEMORY
  | ERROR_BAD_OPTION
  | ERROR_UNKNOWN_TYPE
  | ERROR_UNSUPPORTED_OPERATION
  | ERROR_FAILED
exception GdkPixbufError of gdkpixbuferror * string

(* Creation *)

val create :
  width:int -> height:int ->
  ?bits:int -> ?colorspace:colorspace -> ?has_alpha:bool -> unit -> pixbuf

val cast : 'a Gobject.obj -> pixbuf
external copy : pixbuf -> pixbuf = "ml_gdk_pixbuf_copy"
external subpixbuf : pixbuf -> src_x:int -> src_y:int -> width:int -> height:int -> pixbuf 
  = "ml_gdk_pixbuf_new_subpixbuf"
external from_file : string -> pixbuf = "ml_gdk_pixbuf_new_from_file"
external from_xpm_data : string array -> pixbuf
  = "ml_gdk_pixbuf_new_from_xpm_data"
val from_data :
  width:int -> height:int ->
  ?bits:int -> ?rowstride:int -> ?has_alpha:bool -> Gpointer.region -> pixbuf

val get_from_drawable :
  dest:pixbuf ->
  ?dest_x:int -> ?dest_y:int ->
  ?width:int ->  ?height:int ->
  ?src_x:int -> ?src_y:int ->
  ?colormap:Gdk.colormap -> [>`drawable] Gobject.obj -> unit

(* Accessors *)

external get_n_channels : pixbuf -> int = "ml_gdk_pixbuf_get_n_channels"
external get_has_alpha : pixbuf -> bool = "ml_gdk_pixbuf_get_has_alpha"
external get_bits_per_sample : pixbuf -> int
  = "ml_gdk_pixbuf_get_bits_per_sample"
external get_width : pixbuf -> int = "ml_gdk_pixbuf_get_width"
external get_height : pixbuf -> int = "ml_gdk_pixbuf_get_height"
external get_rowstride : pixbuf -> int = "ml_gdk_pixbuf_get_rowstride"
val get_pixels : pixbuf -> Gpointer.region

(* Rendering *)

val draw_pixbuf :
  [>`drawable] Gobject.obj ->
  Gdk.gc ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int ->
  ?dither:Gdk.Tags.rgb_dither ->
  ?x_dither:int ->
  ?y_dither:int -> ?src_x:int -> ?src_y:int -> pixbuf -> unit

(* obsolete: identical to draw_pixbuf *)
val render_to_drawable :
  [>`drawable] Gobject.obj ->
  ?gc:Gdk.gc ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int ->
  ?dither:Gdk.Tags.rgb_dither ->
  ?x_dither:int ->
  ?y_dither:int -> ?src_x:int -> ?src_y:int -> pixbuf -> unit

val render_alpha :
  Gdk.bitmap ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int -> ?threshold:int -> ?src_x:int -> ?src_y:int -> pixbuf -> unit

val render_to_drawable_alpha :
  [>`drawable] Gobject.obj ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int ->
  ?alpha:alpha_mode ->
  ?threshold:int ->
  ?dither:Gdk.Tags.rgb_dither ->
  ?x_dither:int ->
  ?y_dither:int -> ?src_x:int -> ?src_y:int -> pixbuf -> unit

val create_pixmap : ?threshold:int -> pixbuf -> Gdk.pixmap * Gdk.bitmap option

(* Transform *)

val add_alpha : ?transparent:int * int * int -> pixbuf -> pixbuf

val fill : pixbuf -> int32 -> unit

val saturate_and_pixelate : dest:pixbuf -> saturation:float -> pixelate:bool -> pixbuf -> unit

val copy_area :
  dest:pixbuf ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int -> ?height:int -> ?src_x:int -> ?src_y:int -> pixbuf -> unit

val scale :
  dest:pixbuf ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int ->
  ?ofs_x:float ->
  ?ofs_y:float ->
  ?scale_x:float -> ?scale_y:float -> ?interp:interpolation -> pixbuf -> unit

val composite :
  dest:pixbuf ->
  alpha:int ->
  ?dest_x:int ->
  ?dest_y:int ->
  ?width:int ->
  ?height:int ->
  ?ofs_x:float ->
  ?ofs_y:float ->
  ?scale_x:float -> ?scale_y:float -> ?interp:interpolation -> pixbuf -> unit

(* Saving *)

external save : filename:string -> typ:string -> ?options:(string * string) list -> pixbuf -> unit
    = "ml_gdk_pixbuf_save"
