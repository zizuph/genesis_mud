/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a very narrow room. The only features you " +
	     "can make out are the stairs that lead upwards in " +
	     "a southern direction out of the room and the " +
	     "door leading north.\n");
    
    add_exit(CAVERN + "pal2","north","@@go_through_door");
    add_exit(CAVERN + "b9","up");
    
    DARK;
    
    add_item("stairs","These are ordinary stairs cut out from the stone.\n");
    add_item("door","It's a stone door leading north.\n");
}


go_through_door()
{
    write("You open the door, walk through, and close the door again.\n");
    return 0;
}
