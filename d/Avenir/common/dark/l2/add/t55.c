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

    set_short("eastern gneiss tunnel");
    set_long("This gneiss tunnel was recently connected with "
        +"the one to the northwest. There is a loud whistling sound "
        +"and a strong breeze coming from that direction. There is "
        +"gravel on the ground here, with evidence of footprints.\n");
    
    add_exit("t56", "south",0);
	add_exit("t43", "northwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    ::reset_tunnel_room();
}

