// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t59
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

    set_short("gneiss tunnel");
    set_long("This is a long, low gneiss tunnel running in a north to "
        +"south direction. A breeze blows in from the north and with it "
        +"some haunting musical sounds and the occasional puff of some "
        +"strong musty smell. There is a considerable amount of gravel "
		+"here. The gneiss walls sparkle with crystals and the occasional "
        +"pressure crack, as well as veins of iron and coal.\n");
    
    add_exit("t20", "north",0);
    add_exit("t60", "south",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		
    add_item(({"vein", "veins"}),
	    "There is a vein of iron along the tunnel wall, and a "+
        "vein of coal, too.\n");
    add_item(({"vein of coal", "coal"}), "The coal has been mined by "+
        "someone -- you can see the marks left by tools.\n");
    add_item(({"vein of iron", "iron"}), "The iron here has been mined "+
        "by others over the years.  It looks like this vein is "+
        "nearly exhausted.\n");
    add_item(({"marks", "tool marks"}), "These marks are not "+
        "naturally occuring -- they were made by tools.\n");
		
    ::reset_tunnel_room();
}

