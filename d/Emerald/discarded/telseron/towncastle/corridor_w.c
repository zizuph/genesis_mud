inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Corridor");
    set_long( "To the east you can see some doors on each side of "+
	     "the corridor. The corridor continues to the north from here, "+
	     "descending slightly.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "corridor", "east");
    add_exit(TCASTLE_DIR + "corridor_w1", "north");
}
