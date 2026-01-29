/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("You are on a gravel road leading east and "
	     +    "west through the plains. Brownish grass stretches "
	     +    "out in all directions as far as you can see. "
	     +    "There is a river to the east with a bridge crossing "
	     +    "it.\n");

    add_exit(ROOM + "bridge","east");
    add_exit(ROOM + "road7","west");
    add_invis_exit(ROOM + "river7","north");
    add_invis_exit(ROOM + "river8","south");


    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"plains","grass"}),"These plains are really plain.\n");
    add_item(({"sidearm","river","bridge"}),BS("The river is not very wide, as it is just "
         +  "a sidearm of the mighty Vingaard River, but you sure are glad there "
         +  "is a bridge to get across.",SL));

}



