/* Path to the waterfall
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("Along the bank of a river");
   set_long(
       "You are walking along the bank of a rushing river, a dense forest "+
       "of towering hardwoods and flowering dogwoods pressing in along "+
       "the river's edge. The river turns south here, the forest too "+
       "thick to follow its bank in that direction, though the way "+
       "is clear upstream to the northwest.\n");
 
   add_item(({"forest","woods","trees","hardwoods","dogwoods"}),
      "The forest is a dense mixture of towering hardwoods, their "+
      "branches mingling to form a thick canopy which shades the "+
      "floor of the woods. Flowering dogwoods with their pink and white "+
      "blossoms sprinkle the shade of the forest with their color.\n");
   add_item("river",
      "The river rushes by in a torrent, the dangerous currents flowing "+
      "out of the foothills to the northwest into the valley.\n");
   add_item("valley",
      "It is verdant and dark, grown over with various hardwood trees.\n");
   add_item("foothills",
      "They roll down along the horizon to the west.\n");
   add_item("mountains",
      "They tower high above the foothills along the horizon to the west.\n");
   add_item(({"bank","banks"}),
      "The bank of the river slopes off quickly into the rush of the river, "+
      "but is wide enough to allow passage through the thick forest.\n");
 
   /* exits */
   add_exit("wfpath2","northwest",0);
   add_exit("sfor1","southeast",0);
}
