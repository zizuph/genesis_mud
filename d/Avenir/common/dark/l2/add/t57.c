// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t57.c 
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

    set_short("gneiss cavern with lake");
    set_long("This is the eastern part of a large gneiss cavern that is "
        +"mostly flooded with water to the southwest. There are many "
        +"cracks here in the walls, some of which have fungi growing in "
		+"them. The air is heavy with moisture and a faint musty smell. "
        +"Gravel crunches underfoot with every shift of your weight.\n");
    
    add_exit("t58", "south",0);
	add_exit("t53", "northwest",0);

    /*
     * Put additional add_items below. 
     */
    add_pool();
    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the cavern wall here, "+
        "caused by the stress of all the weight overhead "+
		"and the flow of water through them.\n");	
    add_item(({"mushroom", "mushrooms", "fungi"}), 
        "There are a few different types of mushrooms growing "+
        "here. Some of them might even be useful.\n");
		


    ::reset_tunnel_room();
}

