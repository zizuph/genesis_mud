// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r4.c
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
    set_short("Large chamber");
    set_long("This is a large chamber carved from the wall of the "+
        "massive cavern southeast of here. "+
        "This place appears to be a sleeping area, as there are many "+
        "piles of bedding scattered about, most of them near the "+
        "small fires that light and warm the chamber.\n");


    add_exit("c8", "southeast");


    /*
     * Put additional add_items below. 
     */

    add_carved_room();
    add_fire();
    add_bedding();

    reset_albus_room();
}
