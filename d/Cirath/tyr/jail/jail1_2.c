/* Corridor room 2 on first floor in Jail of Tyr... /*
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
	set_long("A corridor runs from the southeast to the northeast. The "
		+"torches on the wall gives the corridor some light. Two "
		+"chairs stand along the one of the walls. The floor in "
		+"the corridor is full of sand and dust. The walls seems "
		+"to be very old and show signs of neglect.\n");

	add_item("chairs", "It looks like the chairs are a place to sit "
		+"while you wait.\n");

	add_item("corridor", "The corridor runs from the northeast to the "
		+"southeast. It looks well used, guards probably patrols "
		+"the corridor regulary.\n");

	add_item("floor", "Sand and dust is all over the floor.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "Nothing seems to "
		+"happen. You can't manage to remove the torch.\n");

	INSIDE;
	TORCHES;
	WALLS;

	add_exit(TYR_JAIL + "corner1.c", "north", 0,1);
	add_exit(TYR_JAIL + "sleep1.c", "south", 0,1);
	add_exit(TYR_JAIL + "weproom.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail1_4.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail1_1.c", "southeast", 0,1);
	reset_room();
}
