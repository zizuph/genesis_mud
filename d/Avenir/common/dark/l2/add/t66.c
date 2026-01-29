// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t66
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

    set_short("gneiss gnome cavern");
    set_long("A forest of stalagmites and stalactites has grown up here. "
        +"Some of them have been broken off to allow passage through to "
        +"other sides of the cavern. It looks and smells like bat guano "
        +"is being used as fertilizer at the base of the stalactites and "
        +"that a variety of mushrooms are being cultivated for food. "
        +"The darkness and low ceilings are oppressive, as is the smoke "
        +"from the small campfire here.\n");
    

    add_exit("t67", "southeast",0);
	add_exit("t71", "southwest",0);
	add_exit("t69", "northwest",0);

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

