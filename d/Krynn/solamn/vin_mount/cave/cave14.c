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
	SHORT("Tiny natural alcove");
	LONG("Hidden behind a large dripstone formation, this tiny natural "
	+ "alcove has a wooden ladder bolted to the east wall which drops down "
	+ "through the floor.\n");

	ITEM(({"formation", "dripstone", "white dripstone"}), "Formed over many "
	+ "thousands of years of desposits from dripping water, this formation "
	+ "resembles a smooth, wet waterfall frozen in turgid pour.  You are "
	+ "in a tiny alcove behind its top.\n");
	ITEM(({"wooden ladder", "ladder"}), "Rough hewn, dirty, and dotted "
	+ "with a few spots of pale green mold, this ladder has been bolted "
	+ "against the east wall and leads down through the floor.\n");

	DARK;

	EXIT(CAVE + "cave15", "west", 0, 0);
	EXIT(CAVE + "cave12", "down", 0, 0);
}
