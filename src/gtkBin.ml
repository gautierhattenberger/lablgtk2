(* $Id: gtkBin.ml,v 1.18 2003/08/15 11:08:42 garrigue Exp $ *)

open Gaux
open Gtk
open Tags
open GtkBinProps
open GtkBase

external _gtkbin_init : unit -> unit = "ml_gtkbin_init"
let () = _gtkbin_init ()

module Alignment = Alignment

module EventBox = EventBox

module Frame = Frame

module AspectFrame = AspectFrame

module HandleBox = HandleBox

module Viewport = Viewport

module ScrolledWindow = ScrolledWindow

module Socket = Socket

(* module Invisible = Invisible *)
