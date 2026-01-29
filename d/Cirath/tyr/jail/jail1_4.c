/* Corridor room 4 on first floor in Jail of Tyr... /*
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
	set_long("The corridor runs from the southwest to the northeast. The "
		+"only light source in the corridor is some torches that "
		+"hangs on the wall. Guards patrol this corridor regulary. "
		+"Their footprints are obvious in the dust and sand that are "
		+"all over the floor.\n");

	add_item("corridor", "The corridor runs from the southwest to the "
		+"northeast. Guards patrol the corridor regulary.\n");

	add_item(({"dust", "sand"}), "It is all over the floor. It isn't "
		+"easy to clean this floor with this amount of sand.\n");

	add_item("floor", "The floor is covered with sand and dust, making it "
		+"easy to see the footprints of the guards.\n");

	add_item("footprints", "As a result of the sand and dust on the "
		+"floor, you can see the footprints of the guards. The "
		+"footprints goes from the southwest to the northeast.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "You fumble around with "
		+"the torch for a while, but don't manage to move it the "
		+"slightest.\n");

	INSIDE;
	TORCHES;
	WALLS;

	add_exit(TYR_JAIL + "jail1_6.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail1_2.c", "southwest", 0,1);
	reset_room();
}
