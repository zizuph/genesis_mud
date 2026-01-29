inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("End of secret passage");
    set_long( "The passage comes to an abrupt end here. There "+
	     "is no indication that the passage goes any further than this "+
	     "point.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "passage_d", "west");
}
