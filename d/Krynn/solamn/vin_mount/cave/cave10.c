/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object rdog, hob, hob2;

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

	if (!rdog)
	{
		rdog = clone_object(LIV + "rockdog");
		rdog->set_monster_home(CAVE + "cave10");
		rdog->set_restrain_path(CAVE);
		rdog->set_random_move(40);
		rdog->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Small natural cavern");
	LONG("A small natural cavern opens before you with a passageway leading "
	+ "out to the south.  From the ceiling nearly seven meters above hang "
	+ "long stalactites, and portions of the floor are covered with straw "
	+ "and dead leaves.\n");

	ITEM(({"straw", "leaf", "leaves", "dead leaves"}), "The floor has been "
	+ "matted with a layer of straw and dead leaves.  Judging by the weight "
	+ "that must have pressed down upon it, you suspect it has been used as "
	+ "bedding for something large.\n");

	DARK;

	EXIT(CAVE + "cave09", "south", 0, 0);

	reset_vin_mount_room();
}
