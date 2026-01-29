// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e16.c
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
    set_long("The rock-strewn, dirty tunnel continues "+
        "from north to southwest.\n");

    add_exit("e15","north",0,DIRT);
    add_exit("e17","southwest",0,DIRT);

    /*
     * Put additional add_items below. 
     */
    add_item(({"debris", "stone", "dust", "chips", "rock", "rocks"}),
           "The debris is composed mainly of stone dust and rocks, "+
           "chipped from the walls, as yet uncleared remnants of the "+
           "ongoing work in this area.\n");
 

    add_n_tunnel();

    reset_tunnel_room();
}
