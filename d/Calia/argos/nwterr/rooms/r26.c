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
       "northern bank of a rushing river. The surrounding forest " +
       "is sparsely populated with various trees, some in bloom. To "+
       "the southeast you see what seems to be a large gate, set squarely " +
       "in the center of the road, while the road also leads northwest " +
       "along the river's edge. A sturdy wooden bridge spans the river "+
       "to the south.\n");
 
    add_item("trees",
        "Oaks, maples and other stately hardwoods grow in the forest, " +
        "interspersed with flowering dogwood trees, their pink and " +
        "white blooms splashing color throughout the woods.\n");
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the northwest and southeast.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n");
    add_item("forest",
        "Stately oaks and maples grow all around along the " +
        "northern side of the road, interspersed with flowering " +
        "dogwoods, splashing pink and white in the shade of the " +
        "forest's canopy.\n");
    add_item("gate",
        "Gleaming white, it seems to tower above the road to the " +
        "southeast. Perhaps you should get closer to take a better " +
        "look.\n");
    add_item("bridge",
        "Spanning the rushing torrent of the river to the south, " +
        "this wooden bridge looks old, but sturdy. It leads " +
        "to the dense forest on the other bank.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r25","northwest",0);
    add_exit(ROOM_DIR+"r27","southeast",0);
    add_exit(SWTERR_DIR+"rooms/ebridge","south",0);
}
