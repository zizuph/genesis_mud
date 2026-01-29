/* Path to the waterfall
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
       "The foothills of the mountains rise to the west, a rolling base "+
       "of the craggy peaks beyond. The river's flow becomes more peaceful "+
       "as it flows into the gentle slopes of the valley to the southeast, "+
       "but nears the form of rapids as it comes down out of the western "+
       "foothills. The forest grows dense all around, the bank of the river "+
       "the only passage through this rough area.\n");
 
   add_item("river",
      "The river rushes by in a torrent, the dangerous currents flowing "+
      "out of the foothills to the west into the valley to the southeast.\n");
   add_item("valley",
      "It is verdant and dark, grown over with various hardwood trees.\n");
   add_item("foothills",
      "They roll down along the horizon to the west.\n");
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
   add_exit("wfpath3","up","@@doup");
   add_exit("wfpath1","southeast",0);
}
int doup() {
   write("You walk west along the river up into the foothills.\n");
   return 0;
}
