/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 11/12/94  Zima       Created
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
       "You are walking down a dirt road which follows the " +
       "southern bank of a rushing river. A dense forest lines the " +
       "south side of the road, filled with dark trees. The river " +
       "bends toward the northwest at this point, the road following " +
       "the banks like a parallel snake. An arched bridge spans the "+
       "river's width across to the northern bank.\n");
 
    add_item("road",
       "A simple dirt road, newly cleared through the forest, which " +
       "follows a river along its southern bank.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river is filled with oaks and " +
       "maples.\n");
    add_item("bridge",
        "Spanning the rushing torrent of the river to the north, " +
        "this wooden bridge looks old, but sturdy. It leads " +
        "to the dense forest on the other bank.\n");
    add_item(({"forest","trees"}),
        "Dark mohagany trees, many overgrown with vines, grow densely " +
        "around you, their thick canopy making a dark shade on the forest " +
        "floor.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r17","northwest",0);
    add_exit(ROOM_DIR+"r19","east",0);
    add_exit(ROOM_DIR+"wbridge","north",0);
}
