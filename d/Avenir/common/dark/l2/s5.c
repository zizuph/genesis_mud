// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s5.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
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
    set_short("Damp tunnel");
    set_long("This is a natural tunnel that extends to the northeast and "+
        "the west. A brightly lit well carved tunnel leads to the southeast. "+
        "It is very humid here, moisture clings to the walls "+
        "and hangs in the air like a cloud.\n");

    add_exit("s4","northeast",0);
    add_exit("w1","west",0);  
    add_exit("water_pillar", "southeast");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
