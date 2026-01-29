/*
**   ARGOS - Metro - Tritos Road
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
   set_short("Tritos Road");
   set_long(
       "You are walking down the quiet end of Tritos road, the "+
       "city's park framed with a hedge on the west side, and "+
       "the Amphitheatre enclosed with its tall columns to the east. "+
       "A gentle breeze provides a little relief from the sun's "+
       "heat. Tritos continues north and south.\n");
 
   add_item("park",
       "It is surrounded with a well-trimmed hedge which walls the "+
       "road on the west side. You see no entrance to it here.\n");
   add_item("road","It runs north and south.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "The Ampthitheatre of Argos sits on the eastern side of the "+
       "road, an open-air place where citizens "+
       "and visitors alike gather to see dramatic and comic productions. "+
       "It is faced with a line of very tall "+
       "columns which stand in a quarter-circle from its northeastern "+
       "to its southwestern corner. You see no entrance between the "+
       "massive columns here.\n");
   add_item(({"column","columns"}),
       "Standing in a curving line, the columns reach high into the "+
       "sky and form the facade of the Amphitheatre, curving from "+
       "its northeastern to its southwestern corners. Each column "+
       "is topped with a capitol sculpted with happy and sad-faced "+
       "actors' masks.\n");
 
 
   /* exits */
   add_exit(ROOM_DIR+"trroad11","north",0);
   add_exit(ROOM_DIR+"trroad13","south",0);
}
