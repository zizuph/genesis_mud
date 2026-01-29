// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w1.c
// creator(s):       unknown
// revisions:        Casca, 11/21/99
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
    set_short("Well kept tunnel");
    set_long("This is a well kept tunnel. Although mostly natural, someone "+
        "has taken steps to make it more accessible. The floor has been "+
        "leveled and low points in the ceiling have been removed. The area "+
        "has been cleaned of all debris.\n");

  add_exit("w2", "northwest");
  add_exit("s5", "east");  
  add_exit(L4+"w21b", "down");
    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
    add_item(({"floor","ground"}),
        "The ground here is smooth and level. Its obviously "
        + "been worked to obtain this effect in the otherwise "
        + "natural tunnel.\n");
    add_item(({"ceiling","roof","above"}),
        "The ceiling has been worked in places to provide "
        + "for adequate headroom throughout the tunnel.\n");
}

