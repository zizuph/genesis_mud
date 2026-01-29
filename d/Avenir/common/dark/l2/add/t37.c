// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t37.c
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
    set_short("Northern edge");
    set_long("This is the northern edge of a large circular cavern. "+
        "The cavern continues to the south where you can see a large "+
        "object amidst the shadows. An opening to the northeast leads "+
        "into a darkened tunnel.\n");

    add_exit("t34", "southwest", 0);
    add_exit("t35", "southeast", 0);
    add_exit("t36", "south", 0);
    add_exit("t38", "northeast", 0);

    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item("wall",
        "The wall is to the north, it arcs southward as it goes off to "+
        "the east and west.\n");

    reset_tunnel_room();
}

