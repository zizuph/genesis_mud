// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c1.c
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
    set_short("Northeastern corner");
    set_long("You are near the northeastern corner of a large, dimly "+
        "lit cavern. This section of the Utterdark is obviously "+
        "occupied. The stink of soot, burning flesh, and stale "+
        "sweat is overwhelming. "+
        "The cavern has several campfires scattered about it, "+
        "and near the campfires are small tents and piles "+
        "of bedding material. A tunnel goes to the southeast. "+
        "There is a small room carved into the wall north of here.\n");

    add_exit("c2", "south");
    add_exit("t31", "northeast");  
    add_exit("r1", "north");
    add_exit("c6", "west");
    add_exit("c5", "southwest");


    /*
     * Put additional add_items below. 
     */

    add_cavern_room();


    reset_albus_room();

}
