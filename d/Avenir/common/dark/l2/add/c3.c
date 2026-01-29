// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c3.c
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
    set_short("Southeastern corner");
    set_long("You are near the center of the southeast corner of a "+
        "large cavern dimly lit by the glow of several guttering "+
        "campfires. The pop and sizzle of spitted meat dripping "+
        "fat into the coals is so pervasive as to be barely "+
        "noticable.\n");

    add_exit("c5", "northwest");
    add_exit("c4", "west");
    add_exit("c2", "north");


    /*
     * Put additional add_items below. 
     */

    add_cavern_room();


    reset_albus_room();
}
