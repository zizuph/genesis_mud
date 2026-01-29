// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n2.c
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
    set_short("Tunnel");
    set_long("The tunnel bends here, heading south and west "+
        "from this point. Again, it is strangely well-kept, as "+
        "though frequently used.\n");

    add_exit("n1","south",0);
    add_exit("n3","west",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
