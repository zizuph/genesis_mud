// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n1.c
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
    set_long("This wide, well kept tunnel heads north to south here. "+
        "There is little to distinguish it, save that "+
        "the walls and floor are unusually clean.\n");

    add_exit("center","south",0);
    add_exit("n2","north",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
