/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a bend in the hallway, which continues to " +
	     "your southeast, and also to your west, where it " +
	     "leads down at the same time.\n");
    
    add_exit(CAVERN + "har10","southeast");
    add_exit(CAVERN + "har8","west");
    
    DARK;
}
