/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern in the mountain. A narrow passage winds downwards " +
	     "and the cavern extends to the southwest from here.\n");
    
    add_exit(CAVERN + "c5","southwest");
    add_exit(CAVERN + "pass2","down");
    
    DARK;
}

