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
       "You are walking along a steep marble road which winds through a " +
       "range of mountains, surrounded by a sparse forest and large " +
       "boulders. It seems incredibly windy here, though you see no sign " +
       "of bad weather. The road winds up to the summit of the mountains " +
       "to the east, and down the mountain to the west.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It winds along the side of the mountain toward the summit " +
       "to the east, and down towards the foothills to the west.\n");
    add_item(({"forest","trees"}),
        "Pines, firs and other evergreens grow sparsely along " +
        "the landscape of the mountains, interspersed between " +
        "large boulders along the steep mountain face.\n");
    add_item("mountains",
       "Rising towards a summit to the east, and down towards the " +
       "foothills to the west, the mountains are dotted with " +
       "trees and boulders.\n");
    add_item("boulders",
        "Huge mounds of granite, these boulders dot the mountains " +
        "and their foothills, interspersed with the trees of the " +
        "forest.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r8","down","@@dodown");
    add_exit(ROOM_DIR+"r10","up","@@doup");
}
int doup() {
   write("You climb east along the road, higher into the mountains.\n");
   return 0;
}
int dodown() {
   write("You walk down the road to the west.\n");
   return 0;
}
