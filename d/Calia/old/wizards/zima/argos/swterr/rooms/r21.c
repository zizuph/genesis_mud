/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 1/2/94    Zima       Created
** 11/10/95  Zima       Removed bridge across river
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
       "You are standing on a dirt road which follows the " +
       "southern bank of a rushing river. A dark forest lines the " +
       "south side of the road, filled with dark trees. The road " +
       "continues to the east, and bends along the river to the "   +
       "northwest.\n");
 
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
    add_exit(ROOM_DIR+"r20","northwest",0);
    add_exit(ROOM_DIR+"r22","east",0);
}
