(* $Id: gMain.ml,v 1.14 2003/06/24 09:20:02 garrigue Exp $ *)

open Gtk
open GtkMain
open GObj

module Main = Main

module Grab = struct
  open Grab
  let add (w : #widget) = add w#as_widget
  let remove (w : #widget) = remove w#as_widget
  let get_current () = new widget (get_current ())
end

module Rc = Rc

module Timeout = Glib.Timeout

module Idle = Glib.Idle

module Io = Glib.Io

open Main
let main = main
let quit = quit
let init = init

let selection = GData.clipboard Gdk.Atom.primary
let clipboard = GData.clipboard Gdk.Atom.clipboard
