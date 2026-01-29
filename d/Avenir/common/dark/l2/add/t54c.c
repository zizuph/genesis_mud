// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t54c
// creator(s):       Lilith Nov 2021
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/std/room";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_room()
{
    set_short("crack in the wall");
    set_long("There isn't much room here, and between the stench from "
        +"bats nearby and the sliminess of the walls, you're not sure "
        +"how long you'll manage to stay. All you can do is stand here "
        +"in the deep darkness and pretend you're somewhere--anywhere--"
        +"else.\n");
    add_exit("t54b", "back", 0);
	add_exit("t54b", "out", 0, 0, 1);	
    
    IN;
	
    /*
     * Put additional add_items below. 
     */

    add_item(({"fissure", "small fissure"}),
        "This is a small fissure. It might be big enough to "+
        "squeeze your way out of here.\n");		
    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the wall here, "+
        "caused by the stress of all the weight overhead.\n");		
}

