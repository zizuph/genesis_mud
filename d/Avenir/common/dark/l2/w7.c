// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w7.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
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
    set_short("Long curving tunnel");
    set_long("Incredibly long, this tunnel seems to go on forever, "+
        "curving slightly east at the northern end.\n");

    add_exit("w6","south",0);
    add_exit("w8","northeast",0);
  

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
