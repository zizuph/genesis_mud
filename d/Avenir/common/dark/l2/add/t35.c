// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t35.c
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
    set_short("Eastern edge");
    set_long("This is the eastern edge of a large circular cavern. "+
        "The cavern continues towards the west where you can see "+
        "something large looming in the darkness.\n");

    add_exit("t33", "southwest");
    add_exit("t36", "west");
    add_exit("t37", "northwest");

    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item("wall",
        "The wall is to the east, it arcs westward as it goes off to "+
        "the north and south.\n");

    reset_tunnel_room();
}

