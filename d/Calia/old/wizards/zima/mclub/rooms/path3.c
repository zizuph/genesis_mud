/*
**  MCLUB - Memorial Shrine, Outside gate to area
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
   object gate;
 
   set_short("Outside a gate");
   set_long(
      "A large stone arch spans the path through the forest to the east, "+
      "housing a sturdy iron gate which must guard something further "+
      "down the way. The surrounding forest shades the path and fragrances "+
      "the air with the smells of nature. The path through the forest "+
      "leads to the east and west.\n");
 
 
   add_item("arch",
      "It is a large arch built over the path, framing the gate into "+
      "this part of the forest. The arch is built of smooth stones "+
      "which have been cut to fit perfectly into their places in "+
      "the architecture of the arch. An emblem is set in the keystone "+
      "at the top of the arch.\n");
   add_item("keystone",
      "It is the large stone at the top of the arch in the center. "+
      "An emblem is set in it.\n");
   add_item("emblem",
      "Sculpted into the keystone of the arch, the emblem is a "+
      "four-pointed star set within a circle.\n");
   add_item("path",
      "The wide path leads east and west through the trees.\n");
   add_item(({"woods","forest","trees"}),
      "Large trees crowd around the edges of the path, a thick forest "+
      "which of various types of trees, their canopy of branches and "+
      "leaves shading the forest's floor.\n");
 
 
   gate=clone_object(ROOM_DIR+"gateout");
   gate->move(this_object());
   add_exit(ROOM_DIR+"path2","west",0);
}
