// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e1.c
// creator(s):       Tepisch, longtimeago
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
    set_short("Branch in tunnel");
    set_long(
        "Joining with a large cavern to the west, this simple tunnel "+
        "branches toward the east. "+
        "A long stretch of tunnel continues off of the northern branch, "+
        "while towards the south the path curves sharply.\n");

    add_exit("center","west");
    add_exit("e6","northeast");
    add_exit("e2","southeast");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"cavern","large cavern"}),
        "To the east a large cavern can be seen. High-vaulted, "+
        "its ceiling is lost in the shadows.\n");
    add_item(("branch"),
        "To the east the tunnel branches off in two directions, "+
        "much like a 'Y'.\n");

    reset_tunnel_room();
}
