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

    set_short("forked gneiss tunnel");
    set_long("There is a fork in the tunnel here. One branch leads southeast "
        +"and the other, southwest. The main tunnel leads north, into an "
        +"abyssmal darkness. The air is just slightly damp and you can smell "
        +"that there is water nearby. The ground is gravelly underfoot.\n");
    
    add_exit("t60", "north",0);
    add_exit("t12", "southeast",0);
	add_exit("t62", "southwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		

    ::reset_tunnel_room();
}

