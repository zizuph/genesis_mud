// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t
// creator(s):       Lilith Nov 2021
// revisions:   Lilith Dec 2021 added missing add_item
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

    set_short("fissure in the wall");
    set_long("This is a narrow fissure in a gneiss tunnel. The floor "
        +"is slippery with bat guano and fungi, and the acrid smell "
        +"is overpowering. You can hear hundreds of bats overhead "
        +"but it is impossible to see them in such deep darkness. "
        +"There are pressure cracks leading away from the fissure "
		+"deeper into the surrounding stone.\n");
    add_exit("t54", "back", 0);
	add_exit("t54", "out", 0, 0, 1);	
	
    /*
     * Put additional add_items below. 
     */
    add_item(({"floor", "ground", "guano", "bat guano", "layer"}), 
        "There is a thick layer of "+
        "bat guano on the floor here.\n");
    add_item(({"fissure", "small fissure"}),
        "This is a small fissure. It might be big enough to "+
        "squeeze your way out of here.\n");		
    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the wall here, "+
        "caused by the stress of all the weight overhead.\n");		
    add_prop("_av_mine_special", 3);

    ::reset_tunnel_room();
}

