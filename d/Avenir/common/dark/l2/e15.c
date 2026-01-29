// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e15.c
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
    set_long("This dirty, debris-cluttered passageway turns "+
        "slightly to head from northwest to south here. "+
		"Another tunnel leads east into deep shadows.\n");

    add_exit("e14","northwest",0,DIRT);
    add_exit("e16","south",0,DIRT);
	add_exit(L2+"add/t30", "east");

    /*
     * Put additional add_items below. 
     */
    add_item(({"debris", "stone", "dust", "chips"}),
           "The debris is composed mainly of stone dust and chips, "+
           "as yet uncleared remnants of the ongoing work in this area.\n");
 

    add_n_tunnel();

    reset_tunnel_room();
}
