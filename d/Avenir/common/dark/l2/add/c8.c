// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c8.c
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
    set_short("Western wall");
    set_long("You are near the center of the western wall of a large, "+
        "dimly lighted cavern. A sizeable number of people live "+
        "in this cavern, as evidenced by the campfires and bedding "+
        "materials scattered throughout. "+
        "There are two rooms carved into the western wall to the "+
        "northwest and southwest.\n");

    add_exit("c4", "southeast");
    add_exit("r4", "northwest");
    add_exit("r5", "southwest");
    add_exit("c5", "east");
    add_exit("c7", "north");
    add_exit("c6", "northeast");
    

    /*
     * Put additional add_items below. 
     */


    add_cavern_room();

    reset_albus_room();
}
