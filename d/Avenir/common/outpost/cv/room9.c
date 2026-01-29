/* cv/room9.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * talk to Nerull about putting checks on these exits 
 * so non-coven members can only go east. West is where
 * all the goodies are, and north is where the coffins are.
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
	set_short("main intersection");
	set_long("This corridor is an ancient magma tube coated in bands " 
        +"of sea-toned agate. With smooth basaltic floors and crystal-"
        +"encrusted stalactites jutting from the ceiling like so many " 
        +"teeth, there is something simultaneously savage and calming "
        +"about this place. East is a crystal chamber, illuminated by " 
        +"a massive candelabra. North is the sepulchre, and south is " 
        +"the post office. More coven amenities are to the west, up "
        +"steep stairs cut into the basalt."  
		+"\n");

    
    add_exit("tomb",   "north");
	add_exit("room5",  "east");
    add_exit("room10",  "west");
    add_exit("post",   "south");
    // non-obvious exits
    add_exit("room10",  "up", 0, 0, 1);	
	add_exit("room5",   "down", 0, 0, 1);	
		
	add_item(({"stone", "bands", "basalt"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"patterned with bands of colourful agate, and some crystals, too.\n");
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
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this tunnel is draped in darkness that is pierced "
        +"by crystal-encrusted stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness above is so deep that "
        +"even your eyes cannot penetrate it.\n");			

    reset_faerun_room();

}
