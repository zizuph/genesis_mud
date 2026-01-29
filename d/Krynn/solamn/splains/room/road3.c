/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("This is the Solamnian Road leading through the plains. "
	     +  "The road continues northwest and east and the plains "
	     +  "stretches out in all directions.\n");

    add_exit(ROOM + "road2","northwest",0);
    add_exit(ROOM + "road4","east",0);
    add_invis_exit(ROOM + "plain12","north",0,2);
    add_invis_exit(ROOM + "plain31","south",0,2);
    add_invis_exit(ROOM + "plain17","west",0,2);

    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"plains","grass"}),"These plains are really plain.\n");

    set_auto_reset(TABLE);
    reset_room();
}

