// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t65
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
    set_long("The cavern seems to narrow here, as a forest of stalactites "
        +"and stalagmites form barriers to the north and south. Various "
        +"fungi grow around the bases, and you can smell the pungent "
        +"scent of bat guano, which makes you think that the gnomes living " 
        +"here are intentionally cultivating them. There is a steady "
        +"dripping sound from somewhere nearby. There is a small campfire "
		+"built atop the gravel."
        +"\n");
    
    add_exit("t64", "northeast",0);
	add_exit("t68", "northwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"stalactites", "stalagmites", "forest"}),
        "It has taken countless years for these to form from minerals "+
        "leached from the stone by the trickling water. They look like "+
        "a forest of pale, dead trees with fungi growing around the "+
        "bases.\n");		


    ::reset_tunnel_room();
}

