/* cv/room2.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
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
	set_short("crystal tunnel near abyss");
	set_long("A lava tube formed this massive tunnel, melting away "
	    +"stone and leaving behind minerals that formed bands of colour"
        +"ful agate and myriad crystals as it cooled. There is a gentle "
        +"incline to the tunnel leading north from here. South is a "
        +"jagged opening through which you can see a faint orange glow.\n");
     add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled smooth and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");   
	add_item(({"stone", "bands"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"dark with bands of colourful agate, and some crystals, too.\n");
	add_item(({"agate", "colourful agate", "agates", "stripes"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, and lacy swirls.\n");		
    add_item(({"crystal", "crystals", "opening"}),
        "Crystals poke out from every surface, all pointing "
        +"toward the center of the tunnel.\n"); 		
    add_exit("room3", "north");
    add_exit("room1", "south");
    
    reset_faerun_room();

}
