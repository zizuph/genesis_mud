// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c5.c
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
    set_short("Center of cavern");
    set_long("You are near the center of a large cavern so "+
        "dimly illuminated that you can just see the outlines "+
        "of tents and bedrolls near the glowing coals of banked "+
        "campfires.\n");

    add_exit("c4", "south");
    add_exit("c8", "west");
    add_exit("c2", "east");
    add_exit("c6", "north");
    add_exit("c1", "northeast");
    add_exit("c3", "southeast");
    add_exit("c7", "northwest");


    /*
     * Put additional add_items below. 
     */


    add_cavern_room();


    reset_albus_room();
}

