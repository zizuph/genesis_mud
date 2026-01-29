/* Dining-hall on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
	bring_room_mob("slave", TYR_NPC+"jailslav.c", 2);
	bring_room_mob("guard", TYR_NPC+"jailgrd2.c", 1);
}

void
create_room()
{
	set_short("dining-hall");
	set_long("Heavy wooden tables stands against the walls. The tables "
		+"are surrounded by chairs. This is the dining-hall in the "
		+"jail for the guards. The walls is decorated by tapestries "
		+"and a few carvings in the stone wall. There are slaves "
		+"running between this room and the kitchen to the north. "
		+"The floor looks rather clean.\n");

	add_item("floor", "It is clean, probably because this is a dingin-"
		+"hall. Maybe you want to eat in a dirty room.\n");

	add_item("tables", "They look pretty heavy and very steady to eat on. "
		+"The quality of the wood isn't the highest. But what could "
		+"you expect from a place like this. There is food on the "
		+"tables. There might be alot of guards in here soon, if "
		+"they are about to eat that is. Better leave before they "
		+"comes.\n");

	add_item("chairs", "They are of simple brand.\n");

	add_item("walls", "The walls are decorated by different tapestries of "
		+"a simple type. There are also some carvings in the stone "
		+"that the walls are made of. Everything to make the guards "
		+"somewhat content.");

	add_item(({"stone", "carvings"}), "The walls seems to have been "
		+"richly decorated with carvings earlier, but they seem to "
		+"have vanished or been removed. It seems like tapestries "
		+"have been hung up over those carvings that have been "
		+"removed. The removed carvings must have been disliked by "
		+"the High Templar of the jail.\n");

	add_item("tapestries", "The tapestries is of very simply type. It "
		+"seems like the only purpose the are there for, is to cover "
		+"the removed carvings in the stone wall. They pictures "
		+"soldiers and mobs in different locations.\n");

	add_item("slaves", "The slaves looks very busy, maybe you could stop "
		+"one of them and ask them what they are doing and why they "
		+"are hurrying so.\n");

	add_cmd_item(({"slave", "slaves"}), "stop", "You don't seem able to "
		+"stop a slave to ask what they are doing, they just runs "
		+"along mumbling about the food or that they must clean and "
		+"put things in order.\n");

	INSIDE

	add_exit(TYR_JAIL + "groom4.c", "west", 0,1);
	add_exit(TYR_JAIL + "kitchen.c", "north", "@@enter_kitchen",1);
        reset_room();
}

public int
enter_kitchen()
{
	TP->catch_msg("You feel a wonderful smell of food as you enter the "
		+"kitchen.\n");
	return 0;
}
