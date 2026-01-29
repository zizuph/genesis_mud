/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern cast into darkness. Only your light source sheds an " +
	     "eerie light across the stone walls. The cavern extends to the north " +
	     "and to the south from here.\n");
    
    add_exit(CAVERN + "har3","south");
    add_exit(CAVERN + "har5","north");
    
    DARK;
}


