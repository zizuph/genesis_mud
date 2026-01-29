// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t
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

void reset_tunnel_room()
{ 
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_tunnel_room()
{
    add_gneiss_tunnel();
    add_gnome_home();

    set_short("gneiss tunnel");
    set_long("This is a bend in a tunnel that curves from southwest to "
        +"southeast. There is a small crack in the northeast wall, "
        +"through which you can see another tunnel. Southeast is a forest "
        +"of stalagmites and the scent of smoke.\n");
    

    add_exit("t25", "northeast",0);
    add_exit("t65", "southeast",0);
	add_exit("t69", "southwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		
    add_item(({"stalactites", "stalagmites", "forest"}),
        "It has taken countless years for these to form from minerals "+
        "leached from the stone by the trickling water. They look like "+
        "a forest of pale, dead trees from this angle.\n");		


    ::reset_tunnel_room();
}

