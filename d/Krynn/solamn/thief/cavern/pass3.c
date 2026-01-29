/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE


void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a natural cavern. The cavern comes to an end " +
	     "in the north, but continues south. You can see that " +
	     "someone must have enlarged the opening here leading down, " +
	     "cutting some kind of stairs out from the rock.\n");
    
    add_exit(CAVERN + "pass2","south");
    add_exit(CAVERN + "pass4","down");
    
    DARK;
}

