// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t21.c
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
    set_short("Intersection");
    set_long("Three tunnels branch off from here. Two slightly "+
        "worn ones go southeast and west, while an apparently "+
        "unused tunnel goes off to the north. There is a body "+
        "of water east of here, but it isn't accessible from "+
        "here.\n");

    add_exit("t20", "southeast");
    add_exit("t22", "west");
    add_exit("t51", "north");

    /*
     * Put additional add_items below. 
     */

    add_item(({"water", "lake", "river"}), 
        "It's water. Its hard to tell more from here. You'll "+
        "have to figure out how to get closer if you want to "+
        "know more about it.");
		
    add_n_tunnel();

    reset_tunnel_room();
}

