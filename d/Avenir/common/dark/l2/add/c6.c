// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c6.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/albus_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_albus_room()
{
    set_short("Northern wall");
    set_long("You are near the northern wall of a large, "+
        "dimly lit cavern. The cavern's occupancy is evident in "+
        "the profusion of low, smouldering campfires and the small "+
        "tents and bedrolls encircling them.\n");

    add_exit("c5", "south");
    add_exit("c7", "west");
    add_exit("c1", "east");
    add_exit("c2", "southeast");
    add_exit("c8", "southwest");


    /*
     * Put additional add_items below. 
     */

    add_cavern_room();


    reset_albus_room();
}

