/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("You are on a gravel road continuing east and west "
	     +   "in the middle of the Plains of Solamnia. The plains "
	     +   "stretch out to the north and south as far as you can see "
	     +   "and they are covered with brownish grass.\n");

    add_exit(ROOM + "road4","west",0);
    add_exit(ROOM + "road6","east",0);
    add_invis_exit(ROOM + "plain14","north",0,3);
    add_invis_exit(ROOM + "plain33","south",0,3);

    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"plains","grass"}),"These plains are really plain.\n");
 
}


