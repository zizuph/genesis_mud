/* 
 * /d/Kalad/common/wild/pass/w20.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("A picturesque valley spreads out before you, nearly filling "+
      "your entire field of view. Scattered around you are small patches "+
      "of redwood forest, mainly lying along the floor of this valley. The "+
      "number and size of the trees seems to grow less the further west you "+
      "travel. Rising far above the trees are the great Hespyre mountains, "+
      "which cast a dark shadow across the vale. The valley continues to "+
      "the west and east.\n");
   add_item(({"small patches","patches","redwood forest","forest","trees"}),
      "Gigantic trees that are at least twenty feet wide at their base and rise "+
      "dozens upon dozens of feet into the air.\n");
   add_item(({"great hespyre mountains","hespyre mountains","mountains","mountain"}),
      "They tower far above the no less impressive redwood trees, dwarfing "+
      "everything in the land with their size and splendor. So great is "+
      "their height that they cast giant shadows across the vale.\n");
   add_exit("/d/Kalad/common/wild/pass/w21", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w19", "east",0,2);
}
