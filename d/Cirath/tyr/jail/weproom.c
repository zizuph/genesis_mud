/* Weapon storage room on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("storage");
	set_long("The walls are filled with different kinds of weapon racks. "
		+"There are guards placed in this room to guard the weapons, "
		+"so that noone can take them without permission. A desk "
		+"stands against the northern wall. The floor is kept quite "	
		+"clean. When handling weapons a clean environment is a basic "
		+"rule.\n");

	add_item("guards", "They look at you with grim expressions. Their "
		+"eyes are fixed on you. They will not let you get close "
		+"to the weapons without a permission.\n");

	add_item(({"racks", "weapon racks"}), "They hang on the walls or "
		+"stands on the floor. They are of various kind, but one "
		+"thing in common, they are to be used for storing weapons. "
		+"Most of the racks seems to be full of weapons.\n");

	add_item("weapons", "You can see all kinds of weapons in the racks. "
		+"Axes, swords, polarmes, knives, clubs, halberds, mattocks, "
		+"longswords and other weapons.\n");

	add_item("desk", "The desk is covered with weapon parts, tools and "
		+"grindstones. It is used to mend and sharpen weapons on.\n");

	add_item("tools", "The tools is placed on the desk. They are used to "
		+"mend and care weapons with.\n");

	add_item("grindstones", "They look like they are used to sharpen "
		+"weapons with.\n");

	add_item(({"weapon parts", "parts"}), "It is various parts from "
		+"different weapons. Handles, spear tips, knife blades and "
		+"various other parts.\n");

	add_item("floor", "It is clean and kept clean of sand and dust. This "
		+"is a weapon storage room, and weapons don't react well to "
		+"dirt.\n");

	add_cmd_item("weapons", ({"take", "get", "pick"}), "The guards give "
		+"you a grim look which makes you hesitate. You regrets your "
		+"action and leaves the weapons where they are.\n");

	INSIDE

	add_exit(TYR_JAIL + "storage.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail1_2.c", "west", 0,1);
	add_exit(TYR_JAIL + "armroom.c", "east", 0,1);
}
