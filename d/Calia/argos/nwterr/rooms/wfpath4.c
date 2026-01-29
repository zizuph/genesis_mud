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
       "You are making your way through the foothills along the banks of the "+
       "rapids of a wide river, the torrent of water crashing over and round "+
       "the boulders filling the surrounding forest with a constant roar. "+
       "The mountains loom high to the west, craggy and forboding, their "+
       "peaks whipped by strong winds.\n");
 
   add_item("river",
      "The river vortex of rapids crushing over sharp boulders in its "+
      "path. It thunders through the foothills from the north to the "+
      "south.\n");
   add_item("boulders",
      "They dot the rivers path with their sharp edges, the rapids "+
      "crashing and tearing at them constantly.\n");
   add_item("foothills",
      "They roll along the base of the mountains, covered with a dense "+
      "forest.\n");
   add_item("mountains",
      "They tower high beyond the horizon to the west.\n");
   add_item(({"bank","banks"}),
      "The bank of the river slopes off quickly into the rush of the river, "+
      "but is wide enough to allow passage through the thick forest.\n");
   add_item(({"forest","woods","trees","hardwoods","dogwoods"}),
      "The forest is a dense mixture of towering hardwoods, their "+
      "branches mingling to form a thick canopy which shades the "+
      "floor of the woods. Flowering dogwoods with their pink and white "+
      "blossoms sprinkle the shade of the forest with their color.\n");
 
   /* exits */
   add_exit("wfpath5","north",0);
   add_exit("wfpath3","south",0);
}
