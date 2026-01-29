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
    set_long("This is the southeast section of a large cavern. The walls "
        +"have cubbyholes and slots carved into them, and there is a strong "
        +"smell of gnomes here. All about there is evidence that this a "
        +"surprisingly large colony of gnomes. You can't help but wonder "
        +"how they've survived down here in the depths for so long.\n"
        +"There are many footprints in the gravel surrounding a small "
        +"campfire.\n");
    
    add_exit("t62", "northeast",0);
    add_exit("t10", "southeast",0);
	add_exit("t67", "southwest",0);


    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    ::reset_tunnel_room();
}

