/* 
 * /d/Kalad/common/wild/pass/w19.c
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
   set_long("A magnificent valley spreads out before you, nearly filling your "+
      "entire field of view. All about you are giant redwoods, which form "+
      "a forest at the floor of this valley. However, the forest seems less "+
      "dense the further you travel west. Rising far above the trees are "+
      "the great Hespyre mountains, so great are they in height, that they "+
      "cast a dark shadow over the entire vale.\n");
   add_item(({"giant redwoods","redwoods","redwood","forest"}),"Gigantic "+
      "trees that are at least twenty feet wide at their base and rise "+
      "dozens upon dozens of feet into the air.\n");
   add_item(({"great hespyre mountains","hespyre mountains","mountains","mountain"}),
      "They tower far above the no less impressive redwood trees, dwarfing "+
      "everything in the land with their size and splendor. So great is "+
      "their height that they cast giant shadows across the vale.\n");
   add_exit("/d/Kalad/common/wild/pass/w20", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w18", "east",0,2);
}
