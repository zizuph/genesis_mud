// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s1.c
// creator(s):       unknown
// revisions:        Casca, 11/18/99
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
    set_short("Wide tunnel");
    set_long("This area is nearly large enough to earn the classification "+
        "of cavern rather then tunnel. The walls are at least twenty-five "+
        "feet apart from each other and the ceiling far overhead through "+
        "most of the room.\n");

    add_exit("center","north",0);
    add_exit("s2","south",0);


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
