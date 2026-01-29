// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e17.c
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
    set_short("Dirty passageway");
    set_long("The tunnel is quite dirty here, and the dust rises "+
        "to choke you with every step. The passage continues to the "+
        "south and northeast.\n");

    add_exit("e16","northeast",0,DIRT);
    add_exit("s10","southwest",0,DIRT); 

    /*
     * Put additional add_items below. 
     */
    add_item(({"debris", "stone", "dust", "dirt", "chips"}),
           "The debris is composed mainly of stone dust and chips, "+
           "as yet uncleared remnants of the ongoing work in this area.\n");

    add_n_tunnel();

    reset_tunnel_room();
}
