// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t45.c
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
        "from the tread of feet, suggesting somewhat regular traffic. "+
        "The tunnel continues to the northwest while a large cavern "+
        "opens up to the east.\n");

    add_exit("t34", "east", 0);
    add_exit("t46", "northwest", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

