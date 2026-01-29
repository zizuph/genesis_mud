/* Guardroom 3 on first floor in Jail of Tyr... Zayn March 97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd.c", 1, 2);
}

void
create_room()
{
	set_short("guardroom");
	set_long("The walls are empty, besides some weapon racks. There are "
		+"guards sitting here playing cards at a table in one of the "
		+"corners. Empty bottles lay on the floor, both whole and "
		+"broken bottles. The guards look somewhat bored and rather "
		+"ignorant. They are supposed to check who goes into the "
		+"jail and why, and of course see that noone escapes.\n");

	add_item("guards", "It seems like the game is going well for one of "
		+"the guards, he have a rather high pile of coins.\n");

	add_item("table", "Pile of coins are stacked on the table infront of "
		+"each player, a deck of cards lies spread among the coins.\n");

	add_item(({"pile of coins", "pile"}), "Gold, silver, and copper coins "
		+"are stacked in piles, used in the game the guards playes.\n");

	add_item(({"racks", "weapon racks"}), "They are empty right now. "
		+"That is probably because the guards are using their weapons "
		+"right now. The racks are used to store the weapons when they "
		+"are not used.\n");

	add_item(({"bottles", "empty bottles"}), "It looks like some one has "
		+"had a little party here, or it could also be the guards "
		+"drinking to make their time go faster.\n");

	add_cmd_item(({"pile", "pile of coins"}), ({"get", "take", "pick"}), 
		 "As you reach for the money the guards grumbles a warning at "
		+"you. You quickly pull back you hand, you do not want to end "
		+"up in this jail.\n");

	INSIDE

	add_exit(TYR_JAIL + "jailentr.c", "west", 0, 1);
	reset_room();
}
