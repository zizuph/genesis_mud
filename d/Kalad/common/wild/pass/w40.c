/* 
 * /d/Kalad/common/wild/pass/w40.c
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
   set_long("A beautiful vista spreads out before you. What you could "+
      "not see from the Caravan Route to the north is the beautiful "+
      "spectacle of an entire valley filled with towering redwoods. The "+
      "slopes of the Hespyre mountains are less sharp here and are low "+
      "enough in angle that the tree line is significantly higher here than "+
      "on other parts of the mountain range. The vale continues to the "+
      "south.\n");
   add_item(({"towering redwoods","redwoods","towering redwood","redwood"}),
      "Massive trees that are as large as twenty feet across at the base "+
      "and rise dozens of feet into the sky. Their thick canopies of leaves "+
      "in conjunction with their proximity produce an abundance of shade "+
      "beneath them, on the forest floor.\n");
   add_item(({"canopies","canopy","leaves"}),"They nearly block out the "+
      "sky.\n");
   add_item(({"forest floor","floor"}),"The ground is littered with "+
      "newly fallen leaves, still green.\n");
   add_item(({"slopes","hespyre mountains","mountains","mountain","mountain range","range"}),
      "They are perhaps only a third the height of the main mountain range "+
      "of the Hespyre mountains. However, this doesn't make them any less "+
      "impressive, as they are still dozens of times higher than the tallest "+
      "structure made by man.\n");
   add_exit("/d/Kalad/common/wild/pass/w11", "north",0,2);
   add_exit("/d/Kalad/common/wild/pass/w41", "south",0,2);
}
