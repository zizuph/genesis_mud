/* cv/room3.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;


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
	set_short("agate lava tube");
	set_long("The walls of this lava tube have been decorated by the hand "
        +"of nature. Bands of blue, green, and white agate, carnelian, and "	
        +"other minerals seem to swirl and flow past you. The air is cool "  
        +"and fresh, carrying the faintest scent of the sea, while little "
        +"puffs of warmth appear to be coming from the south. West of here "
        +"the tunnel opens onto a massive cathedral-like chamber in the "
        +"basaltic stone deep undergound."
        +"\n");
    
	add_item(({"stone", "bands", "basalt"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"dark with bands of colourful agate, and some crystals, too.\n");
	add_item(({"agate", "colourful agate", "agates", "stripes"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, and lacy swirls.\n");		
    add_item(({"crystal", "crystals", "opening"}),
        "Crystals poke out from every surface, all pointing "
        +"toward the center of the tunnel.\n"); 		
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled level and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");
	add_exit("room4", "west");
    add_exit("room2", "south");
    
    reset_faerun_room();

}
