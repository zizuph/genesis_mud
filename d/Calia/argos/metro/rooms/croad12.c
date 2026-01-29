/*
**   ARGOS - Metro - Chiphas Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Chiphas Road");
   set_long(
       "You are walking down Chiphas road in the middle of Argos, "+
       "the Aeropagus with its line of pillars to the north. A hedge "+
       "parallels the road on the south side, behind which is the "+
       "city park. Chiphas road runs east and west through the heart "+
       "of town, while there is an entrance to the Aeropagus to the "+
       "north.\n");
 
   add_item(({"aeropagus","Aeropagus"}),
       "The Aeropagus is an open-air convocation center of the city. "+
       "It is lined with a set of pillars on this side. There is an "+
       "entrance between the pillars to the north.\n");
   add_item(({"pillar","pillars"}),
       "Tall columns of marble with ornate capitols, they stand "+
       "independently around the Aeropagus like a wall of marble "+
       "trees spaced perfectly apart.\n");
   add_item("road","It runs east and west.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge. You don't see "+
       "an entrance to it here.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"aeropagus", "north",0);
   add_exit(ROOM_DIR+"trroad11", "east",0);
   add_exit(ROOM_DIR+"croad11",  "west",0);
}
