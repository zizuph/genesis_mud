/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is the top of a staircase leading down. A " +
	     "hallway extends out to the east while sloping upwards.\n");
    
    add_exit(CAVERN + "har2","down");
    add_exit(CAVERN + "har9","east");
    
    DARK;
}
