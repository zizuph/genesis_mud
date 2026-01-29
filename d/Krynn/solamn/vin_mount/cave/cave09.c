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
	SHORT("Large natural passage");
	LONG("This large natural passage curves and twists around an abundant "
	+ "formation of white dripstone and continues on in several "
	+ "directions.\n");

	ITEM(({"formation", "dripstone", "white dripstone"}), "Formed over many "
	+ "thousands of years of desposits from dripping water, this formation "
	+ "resembles a smooth, wet waterfall frozen in turgid pour.  Looking "
	+ "more closely towards its base, you notice a dark passage leading "
	+ "east behind it.\n");

	DARK;

	EXIT(CAVE + "cave10", "north", 0, 0);
	EXIT(CAVE + "cave11", "northeast", 0, 0);
	EXIT(CAVE + "cave13", "south", 0, 0);
	EXIT(CAVE + "cave05", "west", 0, 0);
	add_invis_exit(CAVE + "cave12", "east");
}
