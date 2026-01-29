/* Corridor room 3 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 1);
}

void
create_room()
{
	set_short("corridor");
	set_long("The corridor runs from the southwest to the northwest. "
		+"Torches adorn the walls to give the corridor light. The "
		+"kitchen is to the south, it can be recognized by the "
		+"food smell. The guards patroll this corridor regulary. "
		+"There is a crack in the floor at the east wall.\n");

	add_item("crack", "The crack is quite deep. It is hard to say how "
		+"deep it is because it is filled with dust and sand.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "You tries your best "
		+"at pulling the torches but nothing happens.\n");

	INSIDE;
	TORCHES;
	WALLS;

	add_exit(TYR_JAIL + "kitchen.c", "south", "@@enter_kitchen",1);
	add_exit(TYR_JAIL + "library.c", "north", 0,1);
	add_exit(TYR_JAIL + "armroom.c", "west", 0,1);
	add_exit(TYR_JAIL + "jail1_5.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "jail1_1.c", "southwest", 0,1);
	reset_room();
}

public int
enter_kitchen()
{
	TP->catch_msg("You feel a wonderful smell of food as you enter the "
		+"kitchen.\n");
	return 0;
}
