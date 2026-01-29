/* cv/room13.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * Jan 2022: added chute
 *
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
	set_short("West end of the main corridor");
	set_long("This is the west end of the main corridor, just outside the "
        +"armory that holds the coven's stock of weapons and armours. "		
        +"The walls here are striped with purple and red agate bands. "
        +"Crystals sprout from random irregularities in the stone, and "
        +"stalactites extend from the shadows above as if waiting to "
		+"impale intruders. " 
        +"The main corridor of the coven slopes east, down "
		+"toward the cystal chamber and the lounging area.\n"
        +"There is a chute here for disposal of unwanted items."
		+"\n");

    room_add_object("/d/Avenir/common/outpost/cv/obj/chute");  
		
    add_exit("room12", "north");
	add_exit("room10", "east");
	add_exit("armory", "west");
    add_exit("room14", "south");
	
    // non-obvious
	add_exit("room10", "down", 0, 0, 1);	
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
       "The stone appears to be a basalt made when magma cooled. It is "
       +"black and glittering with microcrystals.\n");
    add_item(({"crystal", "crystals", "microcrystals"}),
	    "The Crystals are of every size, from microcrystals sprinkled in "
		+"the basalt to crystals as thick as your thumb sprouting out of "
		+"the walls.\n"); 	
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled level and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");
	add_item(({"ceiling","stalactites", "formations"}),
        "The ceiling of this corridor is draped in darkness that is pierced "
        +"by crystal-encrusted stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness above is so deep that "
        +"even your eyes cannot penetrate it.\n");			
	add_item(({"agate", "colourful agate", "agates", "grape-like",
        "clusters", "stripes", "minerals"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, grape-like clusters, and lacy swirls in reds, "
        +"purples, and white.\n");		

    reset_faerun_room();

}
