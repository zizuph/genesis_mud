inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Base of tower");
    set_long( "You are standing at the base of a tower. There "+
	     "is a winding staircase spiralling upwards. To the north you "+
	     "can see a large hall. There is also some stairs leading down "+
	     "here.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "hall", "north");
    add_exit(TCASTLE_DIR + "tower_middle", "up");
    add_exit(TCASTLE_DIR + "under_tower", "down");
}
