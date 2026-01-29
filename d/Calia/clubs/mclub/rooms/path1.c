/*
**  MCLUB - Memorial Shrine, Path to shrine/hill
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
   set_short("In a tranquil forest");
   set_long(
      "The sounds of the forest begin to quieten as if in some form "+
      "of reverence as you make your way through the dark trees of "+
      "the woods. A mysterious tranquility overcomes you as you "+
      "commune with the silence of nature. You see that you can "+
      "continue deeper into the forest to the northeast, or back to "+
      "the nearby path through some underbrush to the south.\n");
 
   add_item("underbrush",
      "It is a large bundle of dead branches, vines and leaves which hide "+
      "the way into this part of the woods from the path to the south.\n");
   add_item("path",
      "The main path through the forest lies on the other side of "+
      "some undergrowth to the south.\n");
   add_item(({"woods","forest","trees"}),
      "Large trees crowd around you, a thick forest which consists of "+
      "various types of trees, their canopy of branches and "+
      "leaves shading the forest's floor.\n");
   add_item(({"bark","figures"}), "The weathered bark of the old trees "+
            "is black and twisted, like worn and frayed ropes frozen "+
            "in wood.\n");
 
   add_exit(ROOM_DIR+"path2","northeast",0);
   add_exit(OUTSIDE_CONNECTION,"south",0);
}
