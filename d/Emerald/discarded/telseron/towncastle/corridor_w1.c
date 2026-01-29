inherit "/std/room";
 
#include "default.h"


int do_down(string arg);
 
void
create_room()
{
    set_short("Corridor");
    set_long( "The corridor is dropping sharply to the north "+
	     "here - into darkness. To the south you can see the corridor "+
	     "turning to the east and it also looks like it is somewhat "+
	     "lighter there. There are some strange sounds coming from the "+
	     "darkness to the north.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "corridor_w", "south");
    add_exit(TCASTLE_DIR + "corridor_w2", "north");
}
 
void
init()
{
    ::init();
    add_action(do_down, "down");
}
 
int
do_down(string arg)
{
    set_dircmd(arg);
    this_player()->move_living("down", TCASTLE_DIR + "corridor_w2");
    return 1;
}
