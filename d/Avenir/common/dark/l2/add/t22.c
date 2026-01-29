// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t22.c
// creator(s):       Casca, 11/13/99
// revisions:
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
    set_short("Intersection");
    set_long("The slightly worn tunnel that leads east and northwest "+
        "is joined by a rather filthy stinking tunnel that goes off "+
        "to the southeast.\n");

    add_exit("t21", "east", 0);
    add_exit("t23", "southeast", 0);
    add_exit("t33", "northwest", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

