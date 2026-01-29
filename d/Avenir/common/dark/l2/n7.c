// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/n7.c
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
    set_short("Split in Tunnel");
    set_long("This tunnel shows signs of frequent use. It would "+
        "appear the users like to keep it clean, as there is little "+
        "debris laying about.  The tunnel continues to the east. "+
        "A large cavern is off to the west, while a smaller tunnel "+
        "extends to the north.\n");

    add_exit("n8","north");
    add_exit("n4","east");
    add_exit("w8","west");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
