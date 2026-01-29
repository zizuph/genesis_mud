// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e5.c
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
    set_short("Storage room");
    set_long("This is where the miners store the items they need to "+
        "survive away from the city and complete their tasks of "+
        "expanding and maintaining the important tunnels of the "+
        "Utterdark.\n");


    add_exit("e3","northwest");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
