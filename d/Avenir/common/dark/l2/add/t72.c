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
	
    set_short("gneiss tunnel");
    set_long("A tunnel starts here and flows northeast into deep darkness. "
	    +"Part of the gneiss wall to the west has been broken by tools, "
        +"creating a narrow opening to another tunnel. There is a con"
        +"siderable amount of gravel here."
        +"\n");
    
    add_exit("t70", "northeast",0);
	add_exit("t3", "enter", 0, 0, 1); // non-obvious exits
    add_exit("t3", "west", 0, 0, 1);
    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack", "opening"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight above. It "+
        "looks like someone worked to widen one of these cracks "+
        "and succeeded in breaking through to another tunnel.\n");		


    ::reset_tunnel_room();
}

