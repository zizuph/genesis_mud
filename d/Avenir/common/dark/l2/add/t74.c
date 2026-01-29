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

/* Now create the room.  */
void
create_tunnel_room()
{
    add_gneiss_tunnel();
    add_gnome_home();
	
    set_short("gneiss gnome home");
    set_long(" campfire "
        +" "
        +" "
        +"\n");
    
    add_exit("t", "north",0);
    add_exit("t", "northeast",0);
    add_exit("t", "southeast",0);
    add_exit("t", "south",0);
	add_exit("t", "southwest",0);
	add_exit("t", "northwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    reset_tunnel_room();
}

