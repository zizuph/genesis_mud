/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

int numhob = random(6) - 3;
object hob, hob2;

void
reset_vin_mount_room()
{
	if (numhob < 1)
		return;

	if (!hob && numhob >= 1)
	{
		hob = clone_object(LIV + "vmhobgoblin_low");
		hob->move(TO);
	}

	if (!hob2 && numhob == 2)
	{
		hob2 = clone_object(LIV + "vmhobgoblin_low");
		hob2->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Large natural cavern");
	LONG("A large natural cavern opens before you expanding to the south and "
	+ "southwest.  From the ceiling just above hang long stalactites.  From "
	+ "the twisting passage south comes the faint odour of refuse.\n");

	ITEM("refuse", "Though you see no refuse, you catch its odour coming "
	+ "from the south passage.\n");

	DARK;

	EXIT(CAVE + "cave15", "north", 0, 0);
	EXIT(CAVE + "cave20", "south", 0, 0);
	EXIT(CAVE + "cave18", "southwest", 0, 0);
	EXIT(CAVE + "cave17", "west", 0, 0);

	reset_vin_mount_room();
}
