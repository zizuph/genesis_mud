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
	+ "alcove has a wooden ladder bolted to the east wall which climbs high "
	+ "above through the stalactites.  At its base is a small puddle.\n");

	ITEM(({"formation", "dripstone", "white dripstone"}), "Formed over many "
	+ "thousands of years of desposits from dripping water, this formation "
	+ "resembles a smooth, wet waterfall frozen in turgid pour.  You are "
	+ "in a tiny alcove behind it.\n");
	ITEM(({"wooden ladder", "ladder"}), "Rough hewn, soggy, and sporting "
	+ "a pale green mold in spots, this ladder has been bolted against the "
	+ "east wall and leads up through the stalactites.\n");
	ITEM(({"small puddle", "puddle"}), "A small puddle has formed around "
	+ "the base of the ladder from the drops of water coming off the "
	+ "stalactites above.\n");

	DARK;

	EXIT(CAVE + "cave09", "west", 0, 0);
	EXIT(CAVE + "cave14", "up", 0, 0);
}
