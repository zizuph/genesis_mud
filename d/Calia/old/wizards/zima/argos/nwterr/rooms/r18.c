/* ARGOS - NWTERR - Marble Road along river
**
** History:
** Date       Coder          Action
** -------- ------------ -------------------------------------
** 1/93     Zima         Created
** 11/12/95 Zima         Added bridge across river
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road along a river");
   set_long(
       "You are walking down a marble road which runs along the " +
       "northern bank of a rushing river. The river turns eastward " +
       "here, roaring around the curve over boulders in the middle. " +
       "The forest to the north grows densely, preventing you from " +
       "going in that direction, while the forest across the river " +
       "seems dark and forboding. The road follows the river to " +
       "the northwest and east, while a sturdy bridge spans the river "+
       "to the south.\n");
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the northwest and east.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious. You hear the course call of some bird from there.\n");
    add_item("forest",
        "Stately oaks and maples grow densely all around along the " +
        "northern side of the road.\n");
    add_item("bridge",
        "Spanning the rushing torrent of the river to the south, " +
        "this wooden bridge looks old, but sturdy. It leads " +
        "to the dense forest on the other bank.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r17","northwest",0);
    add_exit(ROOM_DIR+"r19","east",0);
    add_exit(SWTERR_DIR+"rooms/wbridge","south",0);
}
