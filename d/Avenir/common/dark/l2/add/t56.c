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
    set_long("A low, narrow tunnel cut from the surrounding gneiss "
        +"rock by the flow of an ancient subterranean river. The walls "
        +"seem to glitter with inset gems. The floor shows evidence of "
		+"many feet passing through. A strong breeze is blowing "
        +"in from the north.\n");
    
    add_exit("t55", "north",0);
    add_exit("t17", "south",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    ::reset_tunnel_room();
}

