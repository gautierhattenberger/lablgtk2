(* $Id: propwin.mli,v 1.4 2000/05/28 20:22:25 fauque Exp $ *)

open Common

val init : unit -> GWindow.window
val show : #tiwidget_base -> unit
val add : #tiwidget_base -> unit
val remove : string -> unit
(* val change_name : string -> string -> unit *)
val update : #tiwidget_base -> bool -> unit
