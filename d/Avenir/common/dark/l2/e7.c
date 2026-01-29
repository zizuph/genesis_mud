// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e7.c
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
    set_short("Tunnel");
    set_long("The tunnel is fairly clean here. The wear of the "+
        "floor indicates that this tunnel is a high traffic area. "+
        "The tunnel continues to the northeast and southwest. "+
        "A dirty tunnel extends towards the southeast.\n");

    add_exit("e6","southwest");
    add_exit("e8","southeast",0,DIRT);
    add_exit("e9","northeast");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
