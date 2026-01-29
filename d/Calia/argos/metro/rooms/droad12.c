/*
**   ARGOS - Metro - Dueteros road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Deuteros Road");
   set_long(
       "The laughter of children floats through the tall well-trimmed "+
       "hedge to the east which surrounds the city park, while one of the "+
       "city's large buildings sits to the west, trimmed with blue "+
       "tile. Deuteros road continues north and south along the edge "+
       "of the park.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south between the park and a large "+
       "structure to the west.\n");
   add_item("building",
       "It a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item("park",
       "It is surrounded with a tall well-trimmed hedge to the east. "+
       "You don't see an entrance to it here.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park. It walls the road on the east side.\n");
   add_item("children",
       "You can't see the children in the park on the other side of the "+
       "hedge, but you can hear their playful laughter.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"droad11", "north",0);
   add_exit(ROOM_DIR+"droad13", "south",0);
}
