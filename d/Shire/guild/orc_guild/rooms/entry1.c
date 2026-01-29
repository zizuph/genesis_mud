
/* 
	*Entrance of the orc race guild cave
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("Inside an entrance to dark cave");

	set_long(short() + ". The cave walls reach up and meet in an arc somewhere overhead. The wan light from outside the cave does not provide enough illumination to see farther inside.\n");
	
	add_item(({"cave"}), "This part of the cave looks quite natural, but farther in the walls take on a more fashioned appearance, as if someone carved them out of the stone.\n");
	add_item(({"entrance"}), "The entrance of the cave is quite narrow compared the the interior, barely allowing two people to enter walking abreast.\n");
	add_item(({"walls", "wall"}), "The walls near the entrance, and the entrance itself, appear to be natural formations of the rock, but farther into the cave, they look more like they were fashioned by tools.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"arc", "ceiling"}), "It is uncertain where the cave walls meet to form the ceiling, as that point becomes so dark that you are not certain if you are seeing the top of the cave or simply shadow.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine.\n");
	
	add_exit("/d/Shire/misty/orc_area/oa6", "out");
	add_exit("/d/Shire/guild/orc_guild/rooms/entry2", "north");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}


