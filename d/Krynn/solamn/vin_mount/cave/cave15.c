/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object hob, hob2, hob3;

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

	if (!hob3)
	{
		hob3 = clone_object(LIV + "vmhobgoblin_low");
		hob3->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Large natural passage");
	LONG("This large natural passage twists around ending at an abundant "
	+ "formation of white dripstone.  It appears to open up into a cavern "
	+ "to the south.\n");

	ITEM(({"formation", "dripstone", "white dripstone"}), "Formed over many "
	+ "thousands of years of desposits from dripping water, this formation "
	+ "resembles the top of a smooth, wet waterfall frozen in turgid pour.  "
	+ "Looking more closely behind it, you notice a dark passage leading "
	+ "east.\n");

	DARK;

	EXIT(CAVE + "cave16", "south", 0, 0);
	add_invis_exit(CAVE + "cave14", "east");

	reset_vin_mount_room();
}
