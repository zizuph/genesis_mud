/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("The road seems to continue endlessly in both directions. " +
	     "There is dried grass surrounding you to the north and south " +
	     "and you feel like it hasn't rained here for a while.\n");

    add_exit(ROOM + "road3","west",0);
    add_exit(ROOM + "road5","east",0);
    add_invis_exit(ROOM + "plain13","north",0,3);
    add_invis_exit(ROOM + "plain32","south",0,3);

    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"plains","grass"}),"These plains are really plain.\n");
  
}


