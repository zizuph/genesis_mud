/* cv/room7.c
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
	set_short("sea agate tunnel");
	set_long("Here, the east-west sea agate tunnel meets up with a "
        +"huge, cathethdral-like chamber to the north. Blue, green, " 
        +"and white bands of agate flow along the walls, creating "
        +"an illusion of being underwater. Tiny crystals shimmer "
        +"as your shadow passes. You can see a trio of huge crystals "
        +"glowing ahead to the north. West is a room containing "
        +"a table and a bulletin board.\n");
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"dark with a hint of warmth, and striped with agate.\n");
    add_item(({"crystal", "crystals"}),
        "Three huge crystals big as wooden beams lean from high up "
        +"on the wall to the floor in the room north of you.\n"); 		
    add_item(({"agate", "colourful agate", "agates", "sea agate", "stripes"}),	
        "Formed eons ago when superheated mineral-rich vapor was trapped "
        +"in the tunnels and then slowly cooled. They are beautiful, "
        +"forming ribbons, bands, and lacy swirls that look like the "
        +"sea in motion.\n");		
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this tunnel is draped in darkness that is pierced "
        +"by stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");	

    add_exit("room6", "north");
	add_exit("room8", "east");
    add_exit("board", "west");
	
    reset_faerun_room();

}
