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
    set_long("The dark is deep and forbidding here in this long tunnel. "
        +"The walls are gneiss, carved and polished by the flow of an "
        +"ancient river eons ago. A strong smell wafts in from the "
		+"southeast, and gravel covers the entire floor."
        +"\n");
    add_exit("t68", "northeast", 0);
    add_exit("t66", "southeast",0);
    add_exit("t70", "southwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		


    ::reset_tunnel_room();
}

