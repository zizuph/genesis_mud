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
	
    set_short("gneiss cavern");
    set_long("This is the southwest end of a low, wide cavern. "
        +"The opening to a narrow tunnel northeast of here is accessible "
        +"through a forest of stalagmites. The floor is gravelly and "
        +"slightly damp. The smoothness of the southern wall is interrupted "
        +"by various recesses and cubbyholes cut into the gneiss. The "
		+"unmistakable scent of gnomes pervades this place.\n");
    
    add_exit("t66", "northeast",0);
	add_exit("t70", "northwest",0);

    /*
     * Put additional add_items below. 
     */

    add_item(({"crack", "pressure crack"}),
        "There are pressure cracks in the tunnel wall here, "+
        "caused by the stress of all the weight overhead.\n");		
   add_item(({"stalactites", "stalagmites", "forest"}),
        "It has taken countless years for these to form from minerals "+
        "leached from the stone by the trickling water. They look like "+
        "a forest of pale, dead trees with fungi growing around the "+
        "bases.\n");		

    ::reset_tunnel_room();
}

