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
       "You are standing on Chiphas road in the heart of Argos, "+
       "between the bustling commercial district to the north and "+
       "the city park to the south. A tall iron fence encloses the "+
       "Strathmos to the north, with an arched gate leading through "+
       "it, while a well-trimmed hedge walls the park "+
       "to the south. Chiphas road continues east and west through "+
       "the city.\n");
 
   add_item(({"shops","establishments","buildings","district",
       "commercial district"}),
       "They are one-level buildings constructed of marble, lining "+
       "the Chiphas on the north side like white cubes.\n");
   add_item("road","It runs east and west.\n");
   add_item("fence",
       "The fence surrounds the Strathmos, sharp spikes "+
       "atop each pole to discourage anyone from scaling it. An "+
       "arched gate leads into the Strathmos to the north.\n");
   add_item("gate",
       "It is an arched entrance through the iron fence to the north.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge. You don't see "+
       "an entrance to it here.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
   add_item(({"strathmos","Strathmos"}),
       "The Strathmos is the depot of the city, where chariots arrive "+
       "to bring in and take out travellers. It is an open-air area "+
       "with a tall iron fence around it. There is a gate leading into "+
       "the Strathmos to the north.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"depot",     "north",0);
   add_exit(ROOM_DIR+"croad12",   "east",0);
   add_exit(ROOM_DIR+"droad11",   "west",0);
}
