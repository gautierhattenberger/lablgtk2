(* $Id: xml_lexer.mli,v 1.1 2001/05/16 03:59:18 garrigue Exp $ *)

type error =
  | Illegal_character of char
  | Bad_entity of string
  | Unterminated of string
  | Tag_expected
  | Other of string
exception Error of error * int
val error_string : error -> string

type token =
  | Tag of string * (string * string) list * bool
        (* [Tag (name, attributes, closed)] denotes an opening tag with
           the specified [name] and [attributes]. If [closed], then the tag
           ended in "/>", meaning that it has no sub-elements. *)
  | Chars of string
        (* Some text between the tags, cut by line *)
  | Endtag of string
        (* A closing tag *)
  | EOF
        (* End of input *)
val token : Lexing.lexbuf -> token
val token_start : unit -> int
