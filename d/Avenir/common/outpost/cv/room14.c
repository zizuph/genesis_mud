/* cv/room14.c
 * Lilith Oct 2021
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
	set_short("north of the grotto");
	set_long("There is a moistness to the air, and a warmth, that seems "
        +"to emanate from south of here. The walls glisten with moisture " 
        +"that deepens the hues of the agate walls and makes the "
        +"myriad crystals sparkle. A large crystal has formed with an "
		+"unusual branching structure that reminds you of a tree. "
        +"There is an intersection to the north.\n");

    add_exit("room13", "north");
	add_exit("grotto", "south");
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"black and glittering with microcrystals.\n");
    add_item(({"crystal", "crystals", "microcrystals"}),
	    "The crystals are of every size, from microcrystals sprinkled in "
		+"the basalt to crystals as thick as your thumb sprouting out of "
		+"the walls.\n");
    add_item(({"tree", "crystal tree", "large crystal"}),
        "It took eons to form a branching crystal of this size. It looks "
        +"a bit like a tree made of glass by a skilled artisan, and it is "
        +"tall enough that you cannot see the top for the shadows up "
		+"above.\n");		
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
