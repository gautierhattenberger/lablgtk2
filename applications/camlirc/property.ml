(* $Id: property.ml,v 1.1.1.1 2002/02/25 07:49:29 garrigue Exp $ *)

module Data = struct
  let data_directory = "data"
end
  
module Interface = struct
  let width = ref 680
  let height = ref 500
  let columns = 6
  let rows = 6
end

module Constants = struct
  let schedule_doctype = "PooMee Schedule 1.1"
end
