/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

void
create_vin_mount_room() 
{
	SHORT("Natural cave passage");
	LONG("This natural passage curves around a bend of stalagmites to the "
	+ "north and east.  Water dripping from stalactites in the ceiling has "
	+ "formed a large puddle here.\n");

	ITEM(({"large puddle", "puddle"}), "A large puddle several centimeters "
	+ "deep has formed on the floor in the southwest corner of the bend from "
	+ "a slow drip above.\n");

	DARK;

	EXIT(CAVE + "cave09", "north", 0, 0);
	EXIT(CAVE + "cave2", "east", 0, 0);
}
