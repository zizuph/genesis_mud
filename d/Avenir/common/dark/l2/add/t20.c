// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t20.c
// creator(s):       Casca, 11/13/99
// revisions:
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
	add_gneiss_tunnel();
    set_short("Tunnel");
    set_long("This is the center of a short tunnel that runs from "+
        "west to east. The walls of the tunnel are fairly smooth, "+
		"polished by the flow of an ancient river. Shadows drape the "+
		"southern wall, while a breeze blows in from the northwest, "+
		"heavy with moisture and an acrid odor.\n");

    add_exit("t19", "east", 0);
    add_exit("t21", "northwest", 0);
	add_exit("t23", "west", 0);
	add_exit("t59", "south", 0, 0, 1);  // non-obvious
	add_exit("t59", "enter", 0, 0, 1);  // non-obvious

    /*
     * Put additional add_items below. 
     */

    add_item(({"shadows", "opening", "hole"}), "It looks like someone "+
        "broke through the wall of the tunnel here from another "+
        "tunnel. The opening is still rough and you can see "+
        "where pickaxes were used to break through the south wall.\n"); 	
    add_item(({"crack", "pressure crack", "pressure cracks"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead. "+
		"There is a large one along the south wall.\n");		
		
    reset_tunnel_room();
}

