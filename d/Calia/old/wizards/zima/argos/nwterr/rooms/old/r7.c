/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road in the foothills");
   set_long(break_string(
       "You are walking along a marble road through the foothills " +
       "of some mountains, surrounded by a dense forest.  The air "  +
       "is a bit cooler here than at the lower levels, and you feel " +
       "refreshed by the gentle mountain breeze.  The road continues " +
       "down onto a forested plain to the west, and east further into " +
       "the foothills.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It leads down onto a plain to the west and east into " +
       "the foothills.\n",70));
 
    add_item("mountains", break_string(
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r6","down",0);
    add_exit(ROOM_DIR+"r8","east",0);
}
