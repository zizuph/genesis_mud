// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n8.c
// creator(s):       unknown
// revisions:        Casca, 11/25/99
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
    set_short("Narrow tunnel");
    set_long("This tunnel is very narrow, the walls seem to be "+
        "closing in on you. The tunnel continues towards the north "+
        "while to the south it opens up into a larger tunnel.\n");

    add_exit("n9","north");
    add_exit("n7","south");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
