// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t46.c
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
    set_short("Damp tunnel");
    set_long("This tunnel is very damp.  The walls glisten with "+
        "a wetness that probably should not be investigated. "+
        "A loud rushing sound "+
        "echoes in from the west.\n");

    add_exit("t45", "southeast", 0);
    add_exit("t47", "west", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

