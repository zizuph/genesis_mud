// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e14.c
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
    set_short("Dirty tunnel");
    set_long("This section of the dirty tunnel narrows significantly "+
        "as it continues to the southeast, while widening to the "+
        "north.\n");

    add_exit("e10","north",0,DIRT);
    add_exit("e15","southeast",0,DIRT);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
