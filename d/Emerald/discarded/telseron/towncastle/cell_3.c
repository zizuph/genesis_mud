inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Dark cell");
    set_long( "The cell is completely bare. There is no "+
	     "indication of what might have made the sounds you heard in "+
	     "the corridor.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    clone_object(TCASTLE_DIR + "doors/cdoor3_b")->move(this_object());
}
