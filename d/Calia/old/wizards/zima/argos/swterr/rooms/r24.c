/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 1/12/93   Zima       Created
** 11/10/95  Zima       Added bridge across river
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A dirt road along a river");
   set_long(
       "You walk along a dirt road which follows the " +
       "southern bank of a rushing river. A black forest lines the " +
       "south side of the road, filled with dark trees. The road " +
       "leads west and east, while a small path leads " +
       "south into the forest.\n");
    add_item("road",
       "A simple dirt road, newly cleared through the forest, which " +
       "follows a river along its southern bank.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river is filled with oaks and " +
       "maples.\n");
    add_item(({"forest","trees"}),
        "Dark mohagany trees, many overgrown with vines, grow densely " +
        "around you, their thick canopy making a dark shade on the forest " +
        "floor.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r23","west",0);
   add_exit(ROOM_DIR+"r25","east",0);
    add_exit(ROOM_DIR+"ogrove1","south",0);
}
