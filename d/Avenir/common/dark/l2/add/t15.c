// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t15.c
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
    set_long("Here two tunnels intersect. "+
        "The tunnel that arcs northeast and northwest seems to "+
        "show signs of the occasional traveler. The tunnel "+
        "that branches off to the south appears rather ominous "+
        "and unused.\n");

    add_exit("t14", "south", 0);
    add_exit("t16", "northeast", 0);
    add_exit("t19", "northwest", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

