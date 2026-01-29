// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e8.c
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
    set_short("Dusty passage");
    set_long("You stand in a dusty, dirty section of the tunnel. "+
        "There is nothing of interest here. "+
        "The tunnel apparently narrows slightly to the south.\n");

    add_exit("e7","northwest",0,DUST);
    add_exit("e10","south",0,DUST);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
