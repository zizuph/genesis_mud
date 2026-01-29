// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t18.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:              DOWN TO L3/W7 HERE
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
    set_short("Cliff top");
    set_long("The tunnel from the south drops nearly straight "+
        "down here. The rubble piled around the east side of the cliff "+
        "should make climbing down relatively safe. "+
        "It appears to be used occasionally judging by the wear "+
        "on the stones.\n");

 //   add_exit("t17", "south");
 //   add_exit(L3 + "l3b/w7", "down"); never opened.

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

