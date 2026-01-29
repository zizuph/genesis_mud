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
   set_short("A marble road through the mountains");
   set_long(
       "You are walking along a marble road in a range of mountains. " +
       "Large boulders are scattered along the landscape between " +
       "sparsely growing trees, " +
       "while a brisk mountain wind ruffles your hair. The road steepens up " +
       "into the heights of the mountains to the east, and leads west " +
       "into the foothills, beyond which you see a forested valley.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads into the foothills to the west, and further " +
       "up into the mountains to the east.\n");
    add_item(({"forest","trees"}),
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n");
    add_item("mountains",
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n");
    add_item("boulders",
        "Huge mounds of granite, these boulders dot the mountains " +
        "and their foothills, interspersed with the trees of the " +
        "forest.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r7","west",0);
    add_exit(ROOM_DIR+"r9","up","@@doup");
}
int doup() {
   write("You walk east along the road, climbing up into the mountains.\n");
   return 0;
}
