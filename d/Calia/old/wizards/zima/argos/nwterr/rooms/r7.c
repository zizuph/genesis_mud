/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 9/15/96  Zima             Cleaned up, messages added to mountain exits
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road in the foothills");
   set_long(
       "You are walking along a marble road through the foothills " +
       "of some mountains, surrounded by a dense forest. The air "  +
       "is a bit cooler here than at the lower levels, and you feel " +
       "refreshed by the gentle mountain breeze. The road continues " +
       "down onto a forested plain to the west, and east further into " +
       "the foothills.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads down onto a plain to the west and east into " +
       "the foothills.\n");
 
    add_item("mountains",
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n");
 
    add_item("forest",
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r6","down","@@dodown");
    add_exit(ROOM_DIR+"r8","east",0);
}
int dodown() {
   write("You walk west along the road down onto the forested plain.\n");
   return 0;
}
