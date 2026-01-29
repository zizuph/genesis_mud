// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t34.c
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
    set_short("Western edge");
    set_long("This is the western edge of a large circular cavern. "+
        "The cavern continues to the east while a tunnel heads off "+
        "to the west. There appears to be something large in the "+
        "center of the cavern but its too dark to make out any details "+
        "from here.\n");

    add_exit("t33", "southeast");
    add_exit("t36", "east");
    add_exit("t37", "northeast");
    add_exit("t45", "west");

    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item("wall",
        "The wall is to the west, it arcs eastward as it goes off to "+
        "the north and south.\n");

    reset_tunnel_room();
}

