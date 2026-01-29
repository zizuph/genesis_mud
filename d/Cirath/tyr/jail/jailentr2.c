/* Entrance-hall to the Jail in Tyr... Zayn March 97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd.c", 2, 1);
}

void
create_room()
{
	set_short("entrence-hall to the Jail");
	set_long("This is the entrence hall to the high templar's tower. "
		+"It was once the home of Pandora the high templar of "
		+"Tyr, but is now the Tyr jail. Both to the east and west "
		+"there are guardrooms. To the north is the jail, maybe you "
		+"should turn around while there's time. This building do not "
		+"look very inviting, there are strange marks on the floor. "
		+"The walls are made of very thick athasian bricks. Once this "
		+"building have been very beautiful, maybe one of the finest "
		+"in Tyr.\n");

	add_item(({"bricks", "athasian bricks", "walls"}), "The walls are made "
		+"of very thick athasian bricks. Bashing through those walls "
		+"would be impossible, so this building would be very suitable "
		+"for a prison.\n");

	INSIDE;
	MARKS;
	STAINS;

	add_exit(TYR_JAIL + "groom3.c", "east", 0, 1);
	add_exit(TYR_JAIL + "groom2.c", "west", 0, 1);
	add_exit(TYR_JAIL + "jail1_1.c", "north", 0, 1);
   add_exit(TYR_JAIL + "jailentr1", "southwest",0,1);
	reset_room();
}
