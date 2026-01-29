// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e11.c
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
    set_short("Center of large cavern");
    set_long("You are in the middle of a large natural gallery. "+
        "The ceiling is far overhead and the walls widely seperated, "+
        "creating a massive chamber that continues to the north and "+
        "south.\n");

    add_exit("e10","southwest");
    add_exit("e12","north");
    add_exit("e13","south");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"ceiling","roof","above"}),"The ceiling is far overhead, "+
        "cloaked in the shadows.\n");

    reset_tunnel_room();
}
