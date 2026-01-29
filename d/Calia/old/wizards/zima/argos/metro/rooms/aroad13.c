/*
**   ARGOS - Metro - Alpharon and Tritos roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
    set_short("Alpharon and Tritos Roads");
   set_long(
       "You come to the intersection of Alpharon and Tritos roads "+
       "on the south side of town. There is an entrance to the northwest "+
       "to the city park, around which grows a well-trimmed hedge. "+
       "Alpharon road runs east and west, bordered by a grove of cherry "+
       "trees on the south, while Tritos leads north between the park "+
       "and one of the city's marble buildings.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along the grove of cherry trees, "+
       "while Tritos leads north.\n");
   add_item("building",
       "It is a long, flat-topped building which stretches to the "+
       "east along the road. You can't make out what might be inside, "+
       "and you don't see an entrance to it here.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
   add_item("park",
       "It lies to the northwest, surrounded by a well-trimmed hedge "+
       "of evergreen.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"trroad14","north",0);
   add_exit(ROOM_DIR+"aroad12", "west",0);
   add_exit(ROOM_DIR+"aroad14", "east",0);
   add_exit(ROOM_DIR+"park6",   "northwest",0);
}
