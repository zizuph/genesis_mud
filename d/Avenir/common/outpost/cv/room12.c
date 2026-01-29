/* cv/room12.c
 * Nerully & Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";



/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    add_prop(ROOM_I_INSIDE, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.	
	set_short("sparkling crystal tunnel");
	set_long("This is the western corridor formed by a tunnel that once "
        +"carried lava flowing south into the abyss. The walls are coated " 
        +"with grape-like clusters of minerals and crystals in red and "
        +"purple hues. The stalactites hanging from the ceiling don't seem "
        +"to be as long here as in the main corridor. The scent of the sea "
        +"wafts in from the north. The supply room lies west of here.\n");	

    add_exit("room11", "north");
    add_exit("room13", "south");
    add_exit("supply", "west");

    
    add_item(({"stone", "bands", "basalt"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"patterned with bands of colourful agate, and some crystals, too.\n");
	add_item(({"agate", "colourful agate", "agates", "grape-like",
        "clusters", "stripes", "minerals"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, grape-like clusters, and lacy swirls in reds, "
        +"purples, and white.\n");		
    add_item(({"crystal", "crystals"}),
        "Crystals poke out from random surfaces, all pointing "
        +"toward the center of the tunnel.\n"); 		
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled level and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");
	add_item(({"ceiling","stalactites", "formations"}),
        "The ceiling of this corridor is draped in darkness that is pierced "
        +"by crystal-encrusted stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness above is so deep that "
        +"even your eyes cannot penetrate it.\n");			
 	
	
    reset_faerun_room();

}
