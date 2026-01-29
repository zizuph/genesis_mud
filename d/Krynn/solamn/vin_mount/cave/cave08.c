/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object hob;

void
reset_vin_mount_room()
{
	if (!hob)
	{
		hob = clone_object(LIV + "vmhobgoblin_low");
		hob->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Chiseled passageway");
	LONG("This three by three meter passage has been mined several meters "
	+ "west to a rough chiseled dead end.  A large natural cavern opens to "
	+ "the east.\n");

	ITEM(({"wall", "walls", "floor", "ground", "ceiling"}), "The walls of "
	+ "this mostly straight passage have been chiseled and mined out.\n");
	ITEM(({"stalactite", "stalactites", "stalagmite", "stalagmites",
	"formation", "formations", "pillar", "pillars"}), "Unlike the rest of "
	+ "this cave system, this passage does not bear such a feature.\n");

	DARK;

	EXIT(CAVE + "cave05", "east", 0, 0);

	reset_vin_mount_room();
}
