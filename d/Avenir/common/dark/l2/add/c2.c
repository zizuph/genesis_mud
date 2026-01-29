// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c2.c
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
    set_short("Eastern wall");
    set_long("You are near the eastern wall of a large "+
        "dimly-lit cavern. The lighting is so poor that "+
        "you can just see the outlines "+
        "of tents and bedrolls near the glowing coals of banked "+
        "campfires.\n");

    add_exit("c3", "south");
    add_exit("c5", "west");
    add_exit("c1", "north");
    add_exit("c6", "northwest");
    add_exit("c4", "southwest");


    /*
     * Put additional add_items below. 
     */

    add_cavern_room();


    reset_albus_room();
}

