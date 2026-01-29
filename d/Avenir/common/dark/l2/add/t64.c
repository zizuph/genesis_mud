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

    set_short("central gneiss cavern");
    set_long("This is the northern section of a large cavern used as living "
        +"quarters by a long-isolated band of gnomes. There are niches and "
        +"cubbies of varying sizes cut into the north wall. The stone of the "
		+"floor is scattered with gravel. The air is humid and redolent with "
        +"the scents of food preparation, fungi, and warm bodies."
        +"\n");
    
    add_exit("t62", "southeast",0);
	add_exit("t65", "southwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		

    ::reset_tunnel_room();
}

