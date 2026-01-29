
/* 
	*Rack room for orc guild
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("A dimly-lit side chamber");

	set_long(short() + ". The walls have been cut from the surrounding stone, very crudely. This chamber is quite messy. Various scraps from broken items are strewn all over. There is, however, a wooden crate here where some items have a chance of being kept out of the way and not stepped on and broken. The torches here shed less than adequate light on the chamber.\n");
	
	add_item(({"chamber"}), "There is not doubt that this part of the cave has been cut and dug out by tools; the walls are too square to be natural.\n");
	add_item(({"walls"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to head heighth. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"torches", "small torches", "weak torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of small sticks. They barely shed any light on the cave.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"room"}), "From where you are standing, not much can be seen from the room east of here. The light in there looks a bit brighter than the light in the passage.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	add_item(({"scraps", "broken items", "leavings", "meals", "old meals", "clothing", "worn out clothing", "worn clothing", "broken weapons"}), "The scraps are mostly unidentifiable. Mostly they are the leavings of old meals, worn out clothing, and broken weapons.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
	
	clone_object("/d/Shire/guild/orc_guild/obj/wood_crate")->move(this_object(), 1);
	
	add_exit("/d/Shire/guild/orc_guild/rooms/passage2", "south");
}
