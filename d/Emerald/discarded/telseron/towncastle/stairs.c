inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Flight of stairs");
    set_long( "You are on a flight of stairs. Below, "+
	     "you can see the castle's entrance hallway, while above "+
	     "there is an opening leading to the battlement running around "+
	     "the entire castle.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "entrance", "down");
    add_exit(TCASTLE_DIR + "battlement", "up");
}
