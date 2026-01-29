// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t50.c
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
    set_short("Tunnel");
    set_long("This tunnel is rather plain. The floor is slightly worn "+
        "from the tread of feet suggesting somewhat regular traffic. "+
        "The tunnel continues to the east while a cavern "+
        "opens up to the west.\n");

    add_exit("t48", "northeast", 0);  
    add_exit(L2 +"e9", "west", 0); 

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

