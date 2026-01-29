/* Corridor room 5 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 1, 1);
}

void
create_room()
{
	set_short("corridor");
	set_long("The walls in this corridor got no torches. Light comes "
		+"from the west room. The only other light source is an "
		+"oil-lamp that stands on a pedestal. A singel chair stands "
		+"at one of the walls. The floor is covered with sand and "
		+"dust, which makes it easy to see the guards footprints on "
		+"the floor.\n");

	add_item("floor", "It is covered with sand and dust. You can see "
		+"footprints in the sand.\n");

	add_item("footprints", "Most of the footprints goes in the "
		+"southeast and the northeast direction. It must be the "
		+"guards patrolling the corridor.\n");

	add_item("chair", "It is a high-backed chair, made of high quality "
		+"wood.\n");

	add_item(({"lamp", "oil-lamp"}), "This is the only light source in "
		+"the corridor. It gives a smoothly warming light. The "
		+"lamp stands on a pedestal.\n");

	add_item("pedestal", "Ontop of the pedestal stands an oil-lamp. "
		+"The pedestal is made of wood and is about one foot in "
		+"diameter, its height is about 3 feet.\n");

	INSIDE;
	WALLS;

	add_exit(TYR_JAIL + "jail1_6.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "office.c", "west", 0,1);
	add_exit(TYR_JAIL + "corner2.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail1_3.c", "southeast", 0,1);
	reset_room();
}
