
/* 
	*Entrance of the orc race guild cave
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("Inside a damp, dark cave");

	set_long(short() + ". A dull light, which comes from a few weak torches lining the walls, allows you to find your way. A distinct feeling of furtive watchfulness fills the cave. There appears to be several rooms branching off here, while the main passage goes no further.\n");
	
	add_item(({"cave"}), "There is not doubt that this part of the cave has been cut and dug out by tools; the walls are too square to be natural.\n");
	add_item(({"walls"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to two meters. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"torches", "small torches", "weak torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of small sticks. They barely shed any light on the cave.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"rooms"}), "From where you are standing, not much can be seen from the rooms.\n");
	add_item(({"passage"}), "The main passage of the cave runs south from here.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_exit("/d/Shire/guild/orc_guild/rooms/start", "northeast");
	add_exit("/d/Shire/guild/orc_guild/rooms/passage1", "south");
	add_exit("/d/Shire/guild/orc_guild/rooms/train", "east");
	add_exit("/d/Shire/guild/orc_guild/rooms/racks", "north");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}
