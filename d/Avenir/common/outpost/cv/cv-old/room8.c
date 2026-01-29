/* cv/room8.c
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
	set_short("crystal tunnel near the abyss");
	set_long("This is the upper end of a short magma tunnel that slopes "
        +"upwards to the west. Its walls are lined with mineral "
        +"deposits overlaying each other to create irridescent "
        +"displays reminiscent of a peacock's feathers. There is "
        +"a faint warmth to the air, which is heated by the magma "
        +"flowing far below to the east, where tremendous forces "
		+"once broke the world.\n");
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"dark with a hint of warmth, and striped with agate.\n");
    add_item(({"crystal", "crystals", "opening"}),
        "Crystals poke out from every surface, all pointing "
        +"toward the center of the tunnel.\n"); 		
    add_item(({"agate", "colourful agate", "agates", "stripes"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, and lacy swirls on the walls of this tunnel.\n");	
	add_item(({"ceiling","stalactites"}),
        "The ceiling of this tunnel is draped in darkness that is pierced "
        +"by stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");			
    add_item(({"air"}), "The air is still with just a hint of warmth.\n");
    add_cmd_item(({"air"}), ({"smell", "sniff"}), 
        "The air smells faintly sulfurous.\n");
		
    add_exit("room7", "west");
	add_exit("room1", "east");

    
    reset_faerun_room();

}
