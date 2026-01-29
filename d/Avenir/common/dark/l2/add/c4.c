// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c4.c
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
    set_short("Southern wall");
    set_long("You are near the southern wall of a large, dimly "+
        "lighted cavern. There are several campfires scattered "+
        "about this section, and near them, small tents and "+
        "piles of bedding material.\n");

    add_exit("c2", "northeast");
    add_exit("c8", "northwest");
    add_exit("c3", "east");
    add_exit("c5", "north");


    /*
     * Put additional add_items below. 
     */


    add_cavern_room();


    reset_albus_room();
}

