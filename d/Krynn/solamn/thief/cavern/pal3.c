/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a straight hallway, which continues to " +
	     "your southeast, and also to your northwest.\n");
    
    add_exit(CAVERN + "pal2","southeast");
    add_exit(CAVERN + "pal4","northwest");
    
    DARK;
}


