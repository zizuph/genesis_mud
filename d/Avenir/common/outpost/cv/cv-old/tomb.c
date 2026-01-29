/* /cv/tomb.c
 *
 * Nerull 2021
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * Talk with Nerull about adding a ck so only 
 * coven members may enter, in the event there
 * is a "removed" member still wandering about. 
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
 	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    remove_prop(ROOM_M_NO_TELEPORT);
    remove_prop(ROOM_M_NO_TELEPORT_TO);
    remove_prop(ROOM_M_NO_TELEPORT_FROM);
    

    set_short("sepulchre");
    set_long("This is the sepulchre of the coven, the place members "
        +"keep their coffins. Chiseled from the stone at the "
		+"root of the mountain, it is an elegantly simple room. "
		+"The black basalt walls have been polished as smooth as "
		+"the floors. While the ceiling appears to be free of the "
        +"stalactites so prevalent elsewhere, it is still cloaked "
        +"in impenetrable shadows. Niches have been carved into the "
        +"east and west walls, each one meant to be claimed by a "
		+"trusted vampire to rest in undisturbed. The north wall "
        +"is bare except for the white marble bier claimed by "
		+"the master of the coven.\n");
	
    add_exit("room9", "south");

	add_item(({"wall", "walls", "basalt walls", "black basalt"}),
        "The stone appears to be basalt columns that formed as magma "
        +"cooled. Every surface has been polished to a high gloss "
        +"that causes the microcrystals to sparkle in even the "
        +"dimmest light. The east and west walls have niches carved "
        +"into them.\n");
    add_item(({"crystal", "crystals", "microcrystals"}),
        "Microcrystals in the basalt sparkle where light catches them.\n");		
    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled level and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");
	add_item(({"ceiling","roof", "dark", "darkness", "shadows"}),
        "The ceiling of this chamber is draped in darkness so deep "
        +"even your eyes cannot penetrate it.\n");			
    add_item(({"niche","niches","east wall","west wall","berth","berths",
        "bunk", "bunks"}),
        "Niches have been cut into the walls. Each one is large enough "
        +"to hold a coffin so that members may rest here in dignity and "
        +"comfort.\n");
    add_item(({"bier", "marble", "marble bier", "white marble bier"}),
        "This is a low rectangular block of white marble intended for the "
		+"coffin of the coven master.\n");
    reset_faerun_room();
}