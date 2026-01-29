inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("End of dark corridor");
    set_long( "The corridor ends here. It is pitch dark and the "+
	     "only way you can go is to the south. There are some sounds "+
	     "coming from behind the cell doors here.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    clone_object(TCASTLE_DIR + "doors/cdoor1_a")->move(this_object());
    clone_object(TCASTLE_DIR + "doors/cdoor2_a")->move(this_object());
    clone_object(TCASTLE_DIR + "doors/cdoor3_a")->move(this_object());
 
    add_exit(TCASTLE_DIR + "corridor_w2", "south");
}
