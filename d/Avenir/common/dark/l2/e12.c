// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e12.c
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
    set_short("Large cavern");
    set_long("You have reached the north end of the long, high cavern.  "+
        "The stone walls here are rough and untouched by human hands "+
        "or tools. The only exit is back into the center of the cavern, "+
        "to the south.\n");

    add_exit("e11","south");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();


    reset_tunnel_room();
}

