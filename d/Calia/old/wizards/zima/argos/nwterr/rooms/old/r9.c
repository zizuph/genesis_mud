/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road through the mountains");
   set_long(break_string(
       "You are walking along a steep marble road which winds through a " +
       "range of mountains, surrounded by a sparse forest and large " +
       "boulders. It seems incredibly windy here, though you see no sign " +
       "of bad weather.  The road winds up to the summit of the mountains " +
       "to the east, and down the mountain to the west.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It winds along the side of the mountain toward the summit " +
       "to the east, and down towards the foothills to the west.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Pines, firs and other evergreens grow sparsely along " +
        "the landscape of the mountains, interspersed between " +
        "large boulders along the steep mountain face.\n",70));
 
    add_item("mountains", break_string(
       "Rising towards a summit to the east, and down towards the " +
       "foothills to the west, the mountains are dotted with " +
       "trees and boulders.\n",70));
 
    add_item("boulders", break_string(
        "Huge mounds of granite, these boulders dot the mountains " +
        "and their foothills, interspersed with the trees of the " +
        "forest.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r8","down",0);
    add_exit(ROOM_DIR+"r10","up",0);
}
