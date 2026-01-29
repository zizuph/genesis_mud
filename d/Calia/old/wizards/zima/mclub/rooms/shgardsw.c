/*
**  MCLUB - Memorial Shrine, North West garden
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("A veranda");
   set_long(
      "You are on the veranda of the stone shrine, an outdoor patio "+
      "area with a round table made of stone encircled by four benches. "+
      "The hill on which the shrine sits has been built up and flattened "+
      "to make this gathering place, overlooking the side of the hill "+
      "and the surrounding forest like a balcony. Entrances lead back "+
      "into the shrine to the north and east.\n");
   add_item("veranda",
      "It is a patio-like area on the side of the hill in a corner "+
      "of the shrine. It is a pleasant place to sit in the sunshine "+
      "and chat with comrades.\n");
   add_item(({"shrine","walls"}),
      "The walls of the shrine are made of large irregular stones "+
      "which mysteriously fit together in perfect harmony. The "+
      "walls form the northern and eastern boundary of the "+
      "veranda area.\n");
   add_item("table",
      "It is a round pedestal-based table, inornate but functional "+
      "in an outdoor area.\n");
   add_item(({"bench","benches"}),
      "Four stone benches surround the table.\n");
   add_item("hill",
      "The hill slopes downward to the southeast, beyond which "+
      "the forest grows darkly.\n");
   add_item(({"forest","trees"}),
      "A dense forest of various trees encircles the hill. Tall oaks grow "+
       "along the hill's base.\n");
   add_item(({"oak","oaks"}), "They tower above the rest of the trees "+
                              "of the surrounding forest.\n");
   add_item(({"entrance","entrances"}),
      "There are entrances back into the shrine to the north and east.\n");
 
   add_exit(ROOM_DIR+"shvestw","north", 0);
   add_exit(ROOM_DIR+"shvests","east",0);
}
