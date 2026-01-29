inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Narrow passage");
    set_long( "You are in a narrow passage stretching north "+
	     "and south. There is some light to the north.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    add_exit(TCASTLE_DIR + "behind_mirror", "south");
    add_exit(TCASTLE_DIR + "bedroom", "north");
}
