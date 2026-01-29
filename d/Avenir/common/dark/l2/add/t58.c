// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t58
// creator(s):       Lilith Nov 2021
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"    
void reset_tunnel_room(){ set_searched(0); ::reset_domain_room(); }

/* Now create the room.  */
void
create_tunnel_room()
{
    add_gneiss_tunnel();

    set_short("gneiss cavern with lake");
    set_long("There is a lake here -- or maybe it is a river -- it's "
        +"difficult to tell in such intense darkness. It takes up most "
        +"of the space in this large cavern. A breeze is blowing in from "
        +"the north. Fungi sprout out of pressure cracks in the walls. "
        +"There are footprints in the gravel.\n");
    
    add_exit("t57", "north",0);
	add_exit("t19", "southwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack", "pressure cracks"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		
    add_item(({"mushroom", "mushrooms", "fungi"}), 
        "There are a few different types of mushrooms growing "+
        "here. Some of them might even be useful.\n");
	

    ::reset_tunnel_room();
}

