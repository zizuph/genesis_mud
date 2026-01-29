/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("The road continues on and on. You are still surrounded "
	     +   "by dried brown grass broken only by the gravel of the road "
	     +   "you are standing on. The road continues east and west. " +
	     "To your south, a river can be seen.\n");

    add_exit(ROOM + "road6","west",0);
    add_exit(ROOM + "road8","east",0);
    add_invis_exit(ROOM + "river6","north",0,3);
    add_invis_exit(ROOM + "river8","southeast",0,3);
    add_invis_exit(ROOM + "river9","southwest",0,3);

    add_item(({"river"}),
	     BS("It is a river, but it's not very wide. The level of the " +
		"water is much lower than the grass, therefore the grass " +
		"is dry despite the presence of the river.",SL));
    add_item(({"road","gravel","gravel road"}),
	     BS("It's just a gravel road.",SL)); 
    add_item(({"ground","plains","grass"}),
	     "These plains are really plain.\n");
 
}



