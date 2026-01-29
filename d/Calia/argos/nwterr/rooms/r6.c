/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 9/15/96  Zima             Cleaned up, messages added to mountain exits
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road");
   set_long(
       "You continue along a marble road through a dense forest. " +
       "The sun shines brightly through the canopy " +
       "of the thick woods, birds fluttering and singing " +
       "all around. The road climbs up into the foothills of some "  +
       "mountains to the east, and continues further west through the "  +
       "forest.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads up into the foothills to the east, and further " +
       "into the forest to the west.\n");
 
    add_item("mountains",
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n");
 
    add_item("forest",
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r5","west",0);
    add_exit(ROOM_DIR+"r7","up","@@doup");
}
int doup() {
   write("You walk east along the road up into the foothills.\n");
   return 0;
}
