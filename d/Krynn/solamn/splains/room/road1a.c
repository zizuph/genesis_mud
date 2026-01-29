/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("You are on the Solamnian Road leading through the "
	     +    "Plains of Solamnia. "
	     +    "To the east and south you can see nothing but "
	     +    "grass all the way to the horizon, whereas in the west and "
	     +    "north there are mountains visible.\n");

    add_exit(ROOM + "road1","northwest",0);
    add_exit(ROOM + "road2","southeast",0);
    add_invis_exit(ROOM + "plain1","north",0,3);
    add_invis_exit(ROOM + "plain5","east",0,3);
    add_invis_exit(ROOM + "plain10","south",0,3);
    add_invis_exit(ROOM + "plain4","west",0,3);

    add_item(({"mountains"}),BS("They are mountains all right, marking the "
	    +"edge of the plains.",SL));
    add_item(({"plains","grass"}),"These plains are really plain.\n");
    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL));
    
}

