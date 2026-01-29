/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road");
   set_long(break_string(
       "You continue along a marble road through a dense forest.  " +
       "The sun shines brightly through the canopy " +
       "of the thick woods, birds fluttering and singing " +
       "all around.  The road climbs up into the foothills of some "  +
       "mountains to the east, and continues further west through the "  +
       "forest.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It leads up into the foothills to the east, and further " +
       "into the forest to the west.\n",70));
 
    add_item("mountains", break_string(
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r5","west",0);
    add_exit(ROOM_DIR+"r7","up",0);
}
