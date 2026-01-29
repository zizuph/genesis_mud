/* Road to the waterfall
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("Along the bank of a river");
   set_long(
      "The flow of the river turns sharply here, spilling out of the "+
      "foothills from the north into the valley to the east. Large "+
      "boulders and the speed of the water churn the river into rapids, "+
      "filling the surrounding forest with a constant but peaceful roar.\n");
 
   add_item("river",
      "The river vortex of rapids crushing over sharp boulders in its "+
      "path. It thunders out of the foothills to the north and turns "+
      "east into the valley.\n");
   add_item("boulders",
      "They dot the rivers path with their sharp edges, the rapids "+
      "crashing and tearing at them constantly.\n");
   add_item("valley",
      "It is verdant and dark, grown over with various hardwood trees. "+
      "The foothills descend into it to the east.\n");
   add_item("foothills",
      "Rolling along the base of the mountains on the western horizon, "+
      "they fall off into the valley to the east.\n");
   add_item("mountains",
      "They tower high beyond the foothills at the horizon to the west.\n");
   add_item(({"bank","banks"}),
      "The bank of the river slopes off quickly into the rush of the river, "+
      "but is wide enough to allow passage through the thick forest.\n");
   add_item(({"forest","woods","trees","hardwoods","dogwoods"}),
      "The forest is a dense mixture of towering hardwoods, their "+
      "branches mingling to form a thick canopy which shades the "+
      "floor of the woods. Flowering dogwoods with their pink and white "+
      "blossoms sprinkle the shade of the forest with their color.\n");
 
   /* exits */
   add_exit("wfpath4","north",0);
   add_exit("wfpath2","down","@@dodown");
}
int dodown() {
   write("You walk east along the river down out of the foothills.\n");
   return 0;
}
