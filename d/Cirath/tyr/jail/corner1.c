/* Cornerroom 1 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("corner room");
	set_long("This room is peculiarly empty, the only furniture is a "
		+"table and two chairs. The chairs stand on opposite sides "
		+"of the table. The floor is clean and free from sand and "
		+"dust. Even the walls are smooth and free from cracks. "
		+"Even though the room is empty, it is lit by a couple of "
		+"torches fastened to the wall.\n");

	add_item("chairs", "The two chairs stand on opposite sides of the "
		+"table. The are made of wood and of rather good quality. "
		+"They are well polished.\n");

	add_item("table", "The surface of the table is polished and totaly "
		+"clean. There are no scratches of any kind. Two chairs "
		+"stand on opposit sides of the table.\n");

	add_item("walls", "The walls are bare and smooth. From distance it "
		+"seems like they were made of marble, but up close it is "
		+"just plain arthasian brick. The only thing on the walls "
		+"are torches to light the room.\n");

	add_item("torches", "The torches give the room light, there are no "
		+"other light sources in this room. There are no windows in "
		+"the walls so the room could recieve some light.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "You fight like a "
		+"maniac to pull the torches on the wall, you can hear a "
		+"soft crack as let go of the torch.\n");

	INSIDE

	add_exit(TYR_JAIL + "jail1_2.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail1_6.c", "east", 0,1);
}
