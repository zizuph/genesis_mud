/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. It is crudely hewn into the mountain, leading " +
	     "north and south from here.\n");
    
    add_exit(CAVERN + "har2","south");
    add_exit(CAVERN + "har4","north");
    
    DARK;
}


