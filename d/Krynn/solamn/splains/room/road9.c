/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("On the road");
    set_long("This is a well traveled road leading north "
	     +    "and south. It is paved and seems to lead to a river in the "
	     +    "south and the road forks to the north.\n");

    add_exit(ROOM + "xroad","north");
    add_exit(ROOM + "ferry","south");

    add_item(({"road","paved road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"river"}),BS("You can't see much of the river yet. "
	 + "Why don't you go take a close look?",SL));
    add_item("fork",BS("You can't make out any details unless you go there.",SL));
 
}



