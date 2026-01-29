/*
 * The Khalakhor Sea Map by Tapakah, October 2021
 * based on the Sparkle Sea Map by Arman
 */

#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "defs.h"

inherit MAP_HANDLER;

// Consult "/d/Khalakhor/ocean/sea-map.txt" for the map legend

nomask void
set_map()
{
  setuid();
  seteuid(getuid());

  string *map_data = explode(read_file(MAP_DATA_FILE), "\n");
  string *match;
  string map_row;
  int line_size, i, to_add;

  Map = ({ });

  foreach (string map_line: map_data) {
    line_size = strlen(map_line);
    if (! line_size)
      break;

    map_row = "";  
    for (i = 0; i < line_size; i++) {
      match = regexp(({map_line[i..i]}), "[a-zA-Z]");
      if (sizeof(match))
        to_add = 1;
      map_row += sizeof(match) ? map_line[i..i] : " ";
    }
    
    if (to_add)
      Map += ({map_row});
  }
  // dump_array(Map);
}
/* file naming convention: 
/* sparkle_sea-a-b-map_letter  

/* 'b'  'a' ->    
/*  | 
/*  0 "",
/*  1 "    msss   nnn",
/*  2 "   mssss ttttttt",
/*  3 " msssssxttt   tte",
/*  4 "  ddsssxtt     te",
/*  5 "   dsssxttt   tte",
/*  6 "   cssss ttttttt",
/*  7 "   cssss   kkk",
/*  8 "  csssss",
/*  9 "   cbbbb",
/* 10 "  cbbbbb",
/* 11 " cbbbbbb",
/* 12 " jbbbbbb",
/* 13 " jbbbbbb",
/* 14 "jbbbbbbb",
/* 15 "jbbbbbbb",
	  });
}
*/
