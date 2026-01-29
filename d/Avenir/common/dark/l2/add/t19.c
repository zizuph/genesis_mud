// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t19.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_tunnel_room()
{
	add_gneiss_tunnel();
    set_short("gneiss tunnel");
    set_long("This tunnel runs from southeast to west, and opens onto "+
        "a large cavern to the northeast. The tunnel seems to be used "+
        "occasionally judging by the wear "+
        "on the floor. There is a body of water to the north--"+
        "either a lake or a river--its hard to tell. It can't be "+
        "reached from here.\n");
    add_exit("t58", "northeast", 0);
    add_exit("t15", "southeast", 0);
    add_exit("t20", "west", 0);

    /* 
     * Put additional add_items below. 
     */
    add_item(({"water", "lake", "river"}), 
        "It's water. Its hard to tell more from here. You'll "+
        "have to figure out how to get closer if you want to "+
        "know more about it.\n");

    reset_tunnel_room();
}

