/*
**   ARGOS - Metro - Alpharon and Protos roads
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
   set_short("Alpharon and Deuteros Roads");
   set_long(
       "You come to the intersection of Alpharon and Deuteros roads "+
       "on the south side of town. Deuteros leads north between one "+
       "of the city's large structures and a park, while Alpharon "+
       "runs east and west along a grove of cherry trees. There is "+
       "an entrance to the park to the northeast through the "+
       "well-trimmed hedge which surrounds it.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west along a grove of cherry trees, "+
       "while Deuteros leads north.\n");
   add_item(({"structure","monument","building"}),
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge. There is an "+
       "entrance to it to the northeast.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"droad14","north",0);
   add_exit(ROOM_DIR+"aroad9", "west",0);
   add_exit(ROOM_DIR+"aroad11","east",0);
   add_exit(ROOM_DIR+"park3",  "northeast",0);
}
