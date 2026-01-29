
/* 
	*Entrance of the orc race guild cave
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>
#include "/d/Shire/guild/orc_guild/orc.h"

inherit "/d/Shire/std/room";

void make_npc();
object orc_guard;

void create_shire_room()
{
	set_short("Inside a damp, dark cave");

	set_long(short() + ". The darkness of the cave entrance has given way to a dull light which comes from a few weak torches lining the walls. Although nothing can be seen of it, sounds of activity can be heard echoing off the walls. A distinct feeling of furtive watchfulness fills the cave. The main passage continues to the northwest.\n");
	
	add_item(({"cave"}), "There is not doubt that this part of the cave has been cut and dug out by tools; the walls are too square to be natural.\n");
	add_item(({"walls"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to head heighth. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"torches", "small torches", "weak torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of small sticks. They barely shed any light on the cave.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"passage", "main passage"}), "The broader route leads off to the northwest, and also south back towards the cave entrance.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_exit("/d/Shire/guild/orc_guild/rooms/entry1", "south");
	//add_exit("/d/Shire/guild/orc_guild/rooms/passage1", "northwest");
	add_exit("/d/Shire/guild/orc_guild/rooms/join", "east");
	add_exit("/d/Shire/guild/orc_guild/rooms/food", "west");
	//add_exit("/d/Shire/guild/orc_guild/rooms/food", "west", "@@block_all@@");
	add_exit("/d/Shire/guild/orc_guild/rooms/passage1", "northwest", "@@check_member@@");
	reset_shire_room();
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}

void reset_shire_room()
{
	make_npc();
}

void make_npc()
{
	if(!orc_guard)
	{
		orc_guard = clone_object("/d/Shire/guild/orc_guild/guild_guard");
		orc_guard->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(orc_guard->query_nonmet_name()))+ " stalks into the cave, growling angrily.\n");
	}
}

int check_member()
{
	if(!IS_MEMBER(TP) && !TP->query_wiz_level())
	{
		write("The orc guard eyes you menacingly. Better not go that way.\n");
		say("The orc guard eyes " + QCTNAME(TP) + " menacingly, blocking " + HIM_HER(TP) + " from going furthing into the cave.\n");
		return 1;
	}
	
	else
		return 0;
}

/*
int block_all()
{
	if(!TP->query_wiz_level())
	{
		write("We're digging out the cave more here, come back later!!\n");
		return 1;
	}
	
	else
		return 0;
}
*/
