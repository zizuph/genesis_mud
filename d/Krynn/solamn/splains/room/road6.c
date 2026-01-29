/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("The Solamnian Road takes you through the plains. "
	     +   "The ground is flat everywhere you look, except for "
	     +   "the gravel of the road under your feet.\n");

    add_exit(ROOM + "road5","west",0);
    add_exit(ROOM + "road7","east",0);
    add_invis_exit(ROOM + "river5","north",0,3);
    add_invis_exit(ROOM + "river9","south",0,3);

    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"ground","plains","grass"}),"These plains are really plain.\n");
 
}

