/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a bend in the hallway, which continues to " +
	     "your northwest, and also to your east. From the " +
	     "east you can hear a monstrous thrashing sound.\n");
    
    add_exit(CAVERN + "har9","northwest");
    add_exit(CAVERN + "har11","east");
    
    DARK;
}


