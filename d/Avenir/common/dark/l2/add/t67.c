// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t67
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
	
    set_short("gneiss gnome home");
    set_long("This is the southern part of a gneiss cavern, home to a tribe "
        +"of gnomes. Numerous niches and cubbies are carved into the wall "
        +"for them to sleep in, which makes sense because the floor is "
        +"covered in gravel. A forest of stalagmites lies northwest of here, "
        +"breaking up the cavern into pockets. At first glance it looks like "
        +"the nearest wall is glistening with droplets of blood, but it turns "
		+"out those are just reddish crystals in the stone. A primitive forge "
        +"has been set up here.\n");
    
    add_exit("t63", "northeast",0);
	add_exit("t66", "northwest",0);

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
    add_item(({"forge", "coals", "crucible"}), 
      "It is very primitive, being constructed mostly of a "
      +"channel of sorts chiseled into a block of gneiss. It is filled "
      +"with hot coals and a small crucible containing melted metal. "
      +"The rest of the block serves as a surface for pounding out "
      +"the metal to form tools and weapons.\n"); 

    ::reset_tunnel_room();
}

