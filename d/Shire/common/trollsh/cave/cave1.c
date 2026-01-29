inherit "/d/Shire/room";
inherit "/d/Shire/common/trollsh/cave/caveroom.c";
#include "/d/Shire/common/defs.h"

void
create_caveroom()
{
   set_short("In a cavern tunnel under the Trollshaws");
   set_long("You have gone down deep into the tunnels "+
   "beneath the Trollshaws, and you wonder if you will "+
   "ever find your way out again. Now and then water drips "+
   "from the ceiling, so much that you wonder where it comes "+
   "from. The tunnel stretches out east and west.\n");

   add_item(({"water","ceiling"}),
   "The water that drips from the mostly smooth ceiling is "+
   "pure and clean, unlike the puddles filled with stagnant "+
   "water.\n");

   add_exit(TROLLSH_DIR + "cave/cave1","west",0,2);

}
