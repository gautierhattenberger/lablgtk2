(* $Id: glib.ml,v 1.20 2004/06/02 20:57:25 oandrieu Exp $ *)

open StdLabels

type unichar = int
type unistring = unichar array

exception GError of string
external _init : unit -> unit = "ml_glib_init"
let () =  _init () ; Callback.register_exception "gerror" (GError "")
exception Critical of string * string

module Main = struct
  type t
  external create : bool -> t = "ml_g_main_new"
  external iteration : bool -> bool = "ml_g_main_iteration"
  external pending : unit -> bool = "ml_g_main_pending"
  external is_running : t -> bool = "ml_g_main_is_running"
  external quit : t -> unit = "ml_g_main_quit"
  external destroy : t -> unit = "ml_g_main_destroy"
  type locale_category =
    [ `ALL | `COLLATE | `CTYPE | `MESSAGES | `MONETARY | `NUMERIC | `TIME ]
  external setlocale : locale_category -> string option -> string 
    = "ml_setlocale"
end

module Timeout = struct
  type id
  external add : ms:int -> callback:(unit -> bool) -> id
    = "ml_g_timeout_add"
  external remove : id -> unit = "ml_g_source_remove"
end

module Idle = struct
  type id
  external add : callback:(unit -> bool) -> id
    = "ml_g_idle_add"
  external remove : id -> unit = "ml_g_source_remove"
end

module Io = struct
  type channel
  type condition = [ `IN | `OUT | `PRI | `ERR | `HUP | `NVAL ]
  external channel_of_descr : Unix.file_descr -> channel
    = "ml_g_io_channel_unix_new"   (* Unix only *)
  external add_watch :
    cond:condition -> callback:(unit -> bool) -> ?prio:int -> channel -> unit
    = "ml_g_io_add_watch"
end

module Message = struct
  type print_func = string -> unit
  external set_print_handler : (string -> unit) -> print_func
    = "ml_g_set_print_handler"

  type log_level =
    [ `ERROR | `CRITICAL | `WARNING | `MESSAGE | `INFO | `DEBUG
    | `FLAG_RECURSION | `FLAG_FATAL ]
  external log_level : log_level -> int = "ml_Log_level_val"

  type log_handler
  external set_log_handler :
    domain:string -> levels:int -> (level:int -> string -> unit) -> log_handler
    = "ml_g_log_set_handler"
  let set_log_handler ~domain ~levels f =
    let levels = List.fold_left levels ~init:0
        ~f:(fun acc lev -> acc lor (log_level lev)) in
    set_log_handler ~domain ~levels f

  external remove_log_handler : log_handler -> unit
    = "ml_g_log_remove_handler"

  let handle_criticals ~domain =
    set_log_handler ~domain ~levels:[`CRITICAL]
      (fun ~level s -> raise (Critical (domain, s)));
    ()

  let () = handle_criticals "GLib"; handle_criticals "GLib-GObject"
end

(*    
module Thread = struct
  external init : unit -> unit = "ml_g_thread_init"
      (* Call only once! *)
  external enter : unit -> unit = "ml_gdk_threads_enter"
  external leave : unit -> unit = "ml_gdk_threads_leave"
end
*)

module Convert = struct
  type error = 
    | NO_CONVERSION
    | ILLEGAL_SEQUENCE
    | FAILED
    | PARTIAL_INPUT
    | BAD_URI
    | NOT_ABSOLUTE_PATH
  exception Error of error * string
  let () = Callback.register_exception "g_convert_error" (Error (NO_CONVERSION, ""))
  external convert :
    string -> to_codeset:string -> from_codeset:string -> string
    = "ml_g_convert"
  external convert_with_fallback :
    ?fallback:string -> to_codeset:string -> from_codeset:string -> string -> string
    = "ml_g_convert_with_fallback"
  external locale_from_utf8 : string -> string
    = "ml_g_locale_from_utf8"
  external locale_to_utf8 : string -> string
    = "ml_g_locale_to_utf8"
  external filename_from_utf8 : string -> string
    = "ml_g_filename_from_utf8"
  external filename_to_utf8 : string -> string
    = "ml_g_filename_to_utf8"
	  
(* [get_charset ()] returns the pair [u,s] where [u] is true if the
   current charset is UTF-8 encoded and [s] is the charset name. *)
  external get_charset : unit -> bool * string = "ml_g_get_charset"

(*  
  external filename_from_uri : string -> string option * string 
    = "ml_g_filename_from_uri"
  external filename_to_uri : string -> string option * string 
    = "ml_g_filename_to_uri"
*)
end

module Unichar = struct
  external to_lower : unichar -> unichar = "ml_g_unichar_tolower"
  external to_upper : unichar -> unichar = "ml_g_unichar_toupper"
  external to_title : unichar -> unichar = "ml_g_unichar_totitle"

  external digit_value : unichar -> int = "ml_g_unichar_digit_value"
  external xdigit_value : unichar -> int = "ml_g_unichar_xdigit_value"

  external validate : unichar -> bool = "ml_g_unichar_validate"
  external isalnum : unichar -> bool = "ml_g_unichar_isalnum"
  external isalpha : unichar -> bool = "ml_g_unichar_isalpha"
  external iscntrl : unichar -> bool = "ml_g_unichar_iscntrl"
  external isdigit : unichar -> bool = "ml_g_unichar_isdigit"
  external isgraph : unichar -> bool = "ml_g_unichar_isgraph"
  external islower : unichar -> bool = "ml_g_unichar_islower"
  external isprint : unichar -> bool = "ml_g_unichar_isprint"
  external ispunct : unichar -> bool = "ml_g_unichar_ispunct"
  external isspace : unichar -> bool = "ml_g_unichar_isspace"
  external isupper : unichar -> bool = "ml_g_unichar_isupper"
  external isxdigit : unichar -> bool = "ml_g_unichar_isxdigit"
  external istitle : unichar -> bool = "ml_g_unichar_istitle"
  external isdefined : unichar -> bool = "ml_g_unichar_isdefined"
  external iswide : unichar -> bool = "ml_g_unichar_iswide"

end

module Utf8 = struct
  external validate : string -> bool = "ml_g_utf8_validate"
  external length : string -> int = "ml_g_utf8_strlen"

  let from_unichar (n : unichar) =
    if n < 0 || n >= 0x4000000 then
      let s = String.create 6 in
      String.unsafe_set s 0 (Char.chr (0xfc + (n lsr 30) land 0b1));
      String.unsafe_set s 1 (Char.chr (0x80 + (n lsr 24) land 0b111111)); 
      String.unsafe_set s 2 (Char.chr (0x80 + (n lsr 18) land 0b111111)); 
      String.unsafe_set s 3 (Char.chr (0x80 + (n lsr 12) land 0b111111));
      String.unsafe_set s 4 (Char.chr (0x80 + (n lsr 6) land 0b111111));
      String.unsafe_set s 5 (Char.chr (0x80 + n land 0b111111));
      s
    else if n <= 0x7f then
      String.make 1 (Char.chr n)
    else if n <= 0x7ff then
      let s = String.create 2 in
      String.unsafe_set s 0 (Char.chr (0xC0 + (n lsr 6) land 0b11111)); 
      String.unsafe_set s 1 (Char.chr (0x80 + n land 0b111111));
      s
    else if n <= 0xffff then
      let s = String.create 3 in
      String.unsafe_set s 0 (Char.chr (0xE0 + (n lsr 12) land 0b1111)); 
      String.unsafe_set s 1 (Char.chr (0x80 + (n lsr 6) land 0b111111));
      String.unsafe_set s 2 (Char.chr (0x80 + n land 0b111111));
      s
    else if n <= 0x1fffff then
      let s = String.create 4 in
      String.unsafe_set s 0 (Char.chr (0xF0 + (n lsr 18) land 0b111));
      String.unsafe_set s 1 (Char.chr (0x80 + (n lsr 12) land 0b111111)); 
      String.unsafe_set s 2 (Char.chr (0x80 + (n lsr 6) land 0b111111));
      String.unsafe_set s 3 (Char.chr (0x80 + n land 0b111111));
      s
    else
      let s = String.create 5 in
      String.unsafe_set s 0 (Char.chr (0xf8 + (n lsr 24) land 0b11));
      String.unsafe_set s 1 (Char.chr (0x80 + (n lsr 18) land 0b111111)); 
      String.unsafe_set s 2 (Char.chr (0x80 + (n lsr 12) land 0b111111));
      String.unsafe_set s 3 (Char.chr (0x80 + (n lsr 6) land 0b111111));
      String.unsafe_set s 4 (Char.chr (0x80 + n land 0b111111));
      s

  let from_unistring (us : unistring) =
    let len = Array.length us in
    let b = Buffer.create (len * 2) in
    for i = 0 to len - 1 do
      Buffer.add_string b (from_unichar us.(i))
    done;
    Buffer.contents b

  let to_unichar s ~pos : unichar =
    let i = !pos in
    let c = Char.code s.[i] in
    if c < 0x80 then (pos := i+1; c) else
    if c < 0xe0 then begin 
      pos := i+2;
      (c - 0xc0) lsl 6 + (Char.code s.[i+1]) - 0x80
    end else if c < 0xf0 then begin
      pos := i+3;
      ((c - 0xe0) lsl 6
         + Char.code s.[i+1] - 0x80) lsl 6
        + Char.code s.[i+2] - 0x80
    end else if c < 0xf8 then begin
      pos := i+4;
      (((c - 0xf0) lsl 6
          + Char.code s.[i+1] - 0x80) lsl 6
         + Char.code s.[i+2] - 0x80) lsl 6
        + Char.code s.[i+3] - 0x80
    end else if c < 0xfc then begin
      pos := i+5;
      ((((c - 0xf8) lsl 6
           + Char.code s.[i+1] - 0x80) lsl 6
          + Char.code s.[i+2] - 0x80) lsl 6
         + Char.code s.[i+3] - 0x80) lsl 6
        + Char.code s.[i+4] - 0x80
    end else begin
      pos := i+6;
      (((((c - 0xf8) lsl 6
            + Char.code s.[i+1] - 0x80) lsl 6
           + Char.code s.[i+2] - 0x80) lsl 6
          + Char.code s.[i+3] - 0x80) lsl 6
         + Char.code s.[i+4] - 0x80) lsl 6
        + Char.code s.[i+5] - 0x80
    end

  let to_unistring s : unistring =
    let len = length s in
    let us = Array.create len 0 in
    let pos = ref 0 in
    for i = 0 to len - 1 do
      us.(i) <- to_unichar s ~pos
    done;
    us

  let first_char s =
    to_unichar s ~pos:(ref 0)
end

module Markup = struct
  external escape_text : string -> string = "ml_g_markup_escape_text"
end
