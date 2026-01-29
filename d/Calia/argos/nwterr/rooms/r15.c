/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 2/22/97  Zima             Argos road extension and cleanup work
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road along a river");
   set_long(
       "You are walking along a marble road which runs along the "+
       "northern bank of a wide river. Along the north side of the "+
       "road the forest of hardwoods grows densely, the shade of "+
       "their canopy of branches speckled with the white and pink "+
       "blossoms of dogwoods. The forest on the other side of the river "+
       "to the south is populated with dark pines. The road continues "+
       "along the river to the west and southeast, while some of the "+
       "trees have been cleared away, leading into the forest to the "+
       "east.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It leads west and southeast along the northern bank of "+
       "the river.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "It turns from the west to the southeast here, flowing by you "+
       "to the south.\n");
    add_item(({"forest","woods","trees","hardwoods","dogwoods"}),
        "Stately oaks, maples and dogwoods grow densely along the north "+
        "side of the road. Across the river to the south, black pines "+
        "populate the river's edge and the valley beyond.\n");
 
    /* exits */
    add_exit("r14b","west",0);
    add_exit("r16","southeast",0);
    add_exit("for1","east",0);
}
