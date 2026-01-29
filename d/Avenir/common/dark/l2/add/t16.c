// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t16.c
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
    set_short("Tunnel");
    set_long("This tunnel runs from southwest to northeast. "+
        "It appears to be used occasionally judging by the wear "+
        "on the floor.\n");

    add_exit("t15", "southwest", 0);
    add_exit("t17", "northeast", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

