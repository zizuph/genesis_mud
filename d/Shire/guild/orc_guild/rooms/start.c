
/* 
	*Start room of the orc race guild cave
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>
#include "/d/Shire/guild/orc_guild/orc.h"

inherit "/d/Shire/std/room";

int okay_to_start;

void create_shire_room()
{
	set_short("A dimly lighted room");

	set_long(short() + ". The walls have been cut from the surrounding stone, very crudely. This appears to be some sort of sleeping chamber, yet there are no bunks of which to speak. Here and there lie orcs who are resting between their shifts working in the cave networks or raiding nearby villages. If you want a corner all to yourself, you will have to fight tooth and nail. 'Claim' an empty spot if you want to sleep here.\n");
	
	add_item(({"room", "chamber", "sleeping chamber"}), "This room looks to have been completely carved out of the stone of one of the walls of the main passage.\n");
	add_item(({"walls", "stone"}), "The walls are completely carved from the rock, and nearly square.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"orcs"}), "The orcs are here catching a brief slumber before returning to their neverending labors.\n");
	add_item(({"corner", "spot"}), "You think you might see an empty spot where you can sleep. Hurry and claim it before someone larger comes and gets it!\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_exit("/d/Shire/guild/orc_guild/rooms/passage2", "southwest");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

init()
{
  ::init();

    add_action("start", "claim");
}

int start(string str)
{
    if(str == "spot" | str == "a spot" | str == "empty spot" | str == "an empty spot")
    {
        TP->set_default_start_location("/d/Shire/guild/orc_guild/rooms/start");
        write("You will awaken to hardship and cruelty here.\n");
        return 1;

    }

    write("Claim a spot?\n");
 
    return 1;
}



