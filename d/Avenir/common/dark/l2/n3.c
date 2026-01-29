// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n3.c
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
    set_short("Clean tunnel");
    set_long("This place is surprisingly clean for a natural tunnel. "+
        "The tunnel continues to the east and west, "+
        "off to the north is a recently excavated opening.\n");

    add_exit("n6","north",0);
    add_exit("n4","west",0);
    add_exit("n2","east",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
