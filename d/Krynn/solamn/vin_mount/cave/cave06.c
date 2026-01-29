/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object rdog, hob1, hob2, hob3;

void
reset_vin_mount_room()
{
	if (!hob1)
	{
		hob1 = clone_object(LIV + "vmhobgoblin_low");
		hob1->move(TO);
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

	if (!rdog)
	{
		rdog = clone_object(LIV + "rockdog");
		rdog->set_monster_home(CAVE + "cave06");
		rdog->set_restrain_path(CAVE);
		rdog->set_random_move(50);
		rdog->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Large natural cavern");
	LONG("A large natural cavern opens before you expanding to the south and "
	+ "west.  From the ceiling nearly seven meters above hang long "
	+ "stalactites, and portions of the floor are covered with straw and "
	+ "dead leaves.  A passageway exits the cavern towards the south.\n");

	ITEM(({"straw", "leaf", "leaves", "dead leaves"}), "The floor has been "
	+ "matted with a layer of straw and dead leaves.  Judging by the weight "
	+ "that must have pressed down upon it, you suspect it has been used as "
	+ "bedding for something large.\n");

	DARK;

	EXIT(CAVE + "cave05", "south", 0, 0);
	EXIT(CAVE + "cave07", "west", 0, 0);

	reset_vin_mount_room();
}
