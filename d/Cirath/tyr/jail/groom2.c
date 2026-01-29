/* Guardroom 2 on first floor in Jail of Tyr... Zayn March 97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd.c", 1, 3);
}

void
create_room()
{
	set_short("guardroom");
	set_long("The walls are empty, besides some weapon racks. To the "
		+"north you can see the office of the captain of the guards. "
		+"The floor is quite clean in here. The chairs and tables "
		+"are also quite clean, it must be because the captain "
		+"passes through here when on his way to his office. "
		+"The guards are supposed to check who goes into the jail "
		+"and why, and of course see that noone escapes.\n");

	add_item(({"racks", "weapon racks"}), "They are empty right now. "
		+"That is probably because the guards are using their weapons "
		+"right now. The racks are used to store the weapons when they "
		+"are not used.\n");

	INSIDE

	add_exit(TYR_JAIL + "jailentr.c", "east", 0, 1);
	add_exit(TYR_JAIL + "groom1.c", "north", 0,1);
	reset_room();
}
