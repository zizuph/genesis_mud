/*
**   ARGOS - Metro - Alpharon Road, at the path to the Palace
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
   set_short("Alpharon Road");
   set_long(
       "The sun suddenly warms your face as it peeks from behind "+
       "whispy clouds as you make your way down Alpharon road. The "+
       "protective hedge of the city park lines the road on the north, "+
       "while a grove of cherry trees grows along the south side, "+
       "its bright blooms perfuming the street.\n");
 
   add_item("clouds",
       "There are very few in the sky, it is a pretty day.\n");
   add_item("sun",
       "Its bright rays warm your face.\n");
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east and west between the tall hedge and the "+
       "grove of cherry trees.\n");
   add_item(({"grove","trees","cherry trees","cherry grove"}),
       "A grove of cherry trees grows along the southern side of "+
       "the street, perfuming the road with their sweet scent.\n");
   add_item("park",
       "It lies to the north and is surrounded by a well-trimmed hedge "+
       "of evergreen.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aroad11", "west",0);
   add_exit(ROOM_DIR+"aroad13", "east",0);
}
