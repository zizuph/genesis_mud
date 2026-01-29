// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t33.c
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
    set_short("Southern edge");
    set_long("This is the southern section of a large circular cavern. "+
        "The cavern extends towards the north where you can see "+
        "something large, while a tunnel opens up to the southeast.\n");

    add_exit("t22", "southeast", 0);
    add_exit("t34", "northwest", 0);
    add_exit("t35", "northeast", 0);
    add_exit("t36", "north", 0);

    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item("wall",
        "The wall is to the south, it arcs northward as it goes off to "+
        "the east and west.\n");

    reset_tunnel_room();
}

