inherit "/std/room";
 
#include "default.h"

int do_up(string arg);

void
create_room()
{
    set_short("Dark corridor");
    set_long( "The corridor is quite dark here. It rises sharply "+
	     "to the south where you think you can make out some light. To "+
	     "the north it is dark as night. There are also some rustling "+
	     "sounds coming from that particular direction.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    add_exit(TCASTLE_DIR + "corridor_w1", "south");
    add_exit(TCASTLE_DIR + "corridor_wend", "north");
}
 
void
init()
{
    ::init();
    add_action(do_up, "up");
}
 
int
do_up(string arg)
{
    set_dircmd(arg);
    this_player()->move_living("up", TCASTLE_DIR + "corridor_w1");
    return 1;
}
