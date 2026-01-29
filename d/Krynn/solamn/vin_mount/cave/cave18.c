/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object hob, hob2;

void
reset_vin_mount_room()
{
	if (!hob)
	{
		hob = clone_object(LIV + "vmhobgoblin_low");
		hob->move(TO);
	}

	if (!hob2)
	{
		hob2 = clone_object(LIV + "vmhobgoblin_low");
		hob2->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Large natural cavern");
	LONG("A large natural cavern opens before you expanding to the north and "
	+ "northeast.  From the ceiling just above hang long stalactites, and a "
	+ "chiseled passage has been mined through the rock wall west.\n");

	ITEM(({"chiseled passage", "passage"}), "Through the rock in the wall to "
	+ "the west has been chiseled a three by three meter passage.\n");

	DARK;

	EXIT(CAVE + "cave17", "north", 0, 0);
	EXIT(CAVE + "cave16", "northeast", 0, 0);
	EXIT(CAVE + "cave19", "west", 0, 0);

	reset_vin_mount_room();
}
