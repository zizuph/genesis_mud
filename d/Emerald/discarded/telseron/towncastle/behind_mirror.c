inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Narrow passage");
    set_long( "You are in the southern end of a narrow passsage. "+
	     "The south wall is nearly transparent, and you suspect you "+
	     "might be able to pass through it.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    add_exit(TCASTLE_DIR + "tower_middle", "south");
    add_exit(TCASTLE_DIR + "passage", "north");
}
