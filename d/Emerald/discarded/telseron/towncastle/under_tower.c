inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Under tower");
    set_long( "This looks like the entrance to some dungeons. There "+
	     "is an old staircase leading up here and what looks like a door "+
	     "opening to the south.\n" );
 
    add_item("door", "The door is gone, only the door frame is left.\n");
    add_item("opening", "It looks like it used to hold a door.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "tower_bottom", "up");
    add_exit(TCASTLE_DIR + "corridor", "south");
}
