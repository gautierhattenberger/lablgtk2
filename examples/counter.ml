(* $Id: counter.ml,v 1.1 2001/02/09 16:08:55 garrigue Exp $ *)

let w = GWindow.window ()

let vb = GPack.vbox ~packing:w#add ()

let lbl = GMisc.label ~packing:vb#pack ()

let hb = GPack.hbox ~packing:vb#pack ()
let decB = GButton.button ~label:"Dec" ~packing:hb#add ()
let incB = GButton.button ~label:"Inc" ~packing:hb#add ()

let adj =
  GData.adjustment ~lower:0. ~upper:100. ~step_incr:1. ~page_incr:10. ()
let sc = GRange.scale `HORIZONTAL ~adjustment:adj ~draw_value:false
    ~packing:vb#pack ()

let counter = new GUtil.variable 0

open GMain

let _ =
  decB#connect#clicked
    ~callback:(fun () -> adj#set_value (float(counter#get-1)));
  incB#connect#clicked
    ~callback:(fun () -> adj#set_value (float(counter#get+1)));
  adj#connect#value_changed
    ~callback:(fun () -> counter#set (truncate adj#value));
  counter#connect#changed ~callback:(fun n -> lbl#set_text (string_of_int n));
  counter#set 0;
  w#connect#destroy ~callback:Main.quit;
  w#show ();
  Main.main ()
