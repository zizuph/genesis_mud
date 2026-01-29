/* cv/supply.c
 * Nerull & Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * 
 * Lilith Mar 2022: Changed the path for the rack for this room.
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
	set_short("supply room");
	set_long("Located between the armoury and the roost, this room "
        +"is where the coven stores its supplies. Columns of basalt " 
        +"form the walls and the floor, which has been polished to a "
        +"high sheen. High above, stalagmites hanging from the ceiling "
        +"are encrusted with crystals. The entire western wall has a "
        +"rack bolted to it to help keep things organized. "
		+"\n");

// This is a second instance of the first--the two racks were over-writing 
// each other depending on which loaded first.
// --Lilith Mar 2022		
//    room_add_object(VAMPIRES_GUILD_DIR + "obj/cv2_rack");
// Created a second rack with its own .o save file.
    room_add_object("/d/Avenir/common/outpost/cv/obj/cv2_rack2");
	

    add_item(({"floor", "ground", "basalt floor"}),
        "The basalt floor is chiseled smooth and polished to a high gloss "
        +"that accentuates the sparkle of the microcrystals within it.\n");   
	add_item(({"stone", "walls", "basalt", "basalt column", "columns"}),
        "The stone of the walls appears to be basalt that formed as magma cooled. It is "
        +"dark with a flight reddish tiny, and is peppered with crystals, too.\n");
    add_item(({"crystal", "crystals", "ceiling", "stalagmites"}),
        "Small crystals can be seen growing on the stalgmites that "
        +"have formed on the ceiling.\n"); 		
    add_exit("armory", "south");
	add_exit("room12", "east");

    reset_faerun_room();

}
