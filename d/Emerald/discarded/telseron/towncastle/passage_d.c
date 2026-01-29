inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Secret passage");
    set_long( "The passage is quite low, going in an east-west "+
	     "direction. It looks like it ends just east of here, and to "+
	     "the west it appears to turn southwards.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "passage_e", "east");
    add_exit(TCASTLE_DIR + "passage_w", "west");
}
