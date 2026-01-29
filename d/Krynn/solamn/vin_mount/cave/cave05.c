/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object rdog, hob;

void
reset_vin_mount_room()
{
	if (!hob)
	{
		hob = clone_object(LIV + "vmhobgoblin_low");
		hob->move(TO);
	}

	if (!rdog)
	{
		rdog = clone_object(LIV + "rockdog");
		rdog->set_monster_home(CAVE + "cave05");
		rdog->set_restrain_path(CAVE);
		rdog->set_random_move(50);
		rdog->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Large natural cavern");
	LONG("A large natural cavern opens before you expanding to the north and "
	+ "northwest.  From the ceiling nearly seven meters above hang long "
	+ "stalactites.  A natural passageway leads east, and to the west a "
	+ "chiseled passage has been mined out.\n");

	DARK;

	EXIT(CAVE + "cave06", "north", 0, 0);
	EXIT(CAVE + "cave09", "east", 0, 0);
	EXIT(CAVE + "cave03", "south", 0, 0);
	EXIT(CAVE + "cave08", "west", 0, 0);
	EXIT(CAVE + "cave07", "northwest", 0, 0);

	reset_vin_mount_room();
}
