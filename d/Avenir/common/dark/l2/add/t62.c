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
void reset_tunnel_room(){ set_searched(0); ::reset_domain_room(); }

/* Now create the room.  */
void
create_tunnel_room()
{
    add_gneiss_tunnel();
	add_gnome_home();

    set_short("gneiss gnome cavern");
    set_long("This is the northeast section of a large cavern that shows "
        +"evidence of being a living quarters. The gneiss walls have been "
        +"painstakingly chiseled away to make recesses for sitting and "
        +"sleeping in. Many footprints mark the gravel. There is a "
        +"distinctive scent to the area, one you've come to associate with "		
        +"gnomes. There is a small campfire built here.\n");
    
    add_exit("t61", "northeast",0);
	add_exit("t63", "southwest",0);
	add_exit("t64", "northwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    ::reset_tunnel_room();
}

