/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

object sgoblin;

void
reset_vin_mount_room()
{
	if (!objectp(sgoblin))
	{
		sgoblin = clone_object(LIV + "sneak_goblin");
		sgoblin->move(TO);
	}
}

void
create_vin_mount_room() 
{
	SHORT("Alcove in a cave");
	LONG("The passageway ends here in a natural alcove and slopes down to "
	+ "the east where a crack in the wall leads out into a passageway.  "
	+ "Straw and dead leaves have been matted down here softening and "
	+ "leveling out the uneven floor.\n");

	ITEM(({"straw", "leaf", "leaves", "dead leaves"}), "The floor has been "
	+ "matted with a layer of straw and dead leaves.  Judging by the weight "
	+ "that must have pressed down upon it, you suspect it has been used as "
	+ "bedding for something large.\n");
	ITEM(({"flicker", "torchlight"}), "Your eyes barely detect the flicker "
	+ "of torchlight to the south.\n");
	ITEM("crack", "You spot a long crack in the eastern wall.  It folds over "
	+ "concealing its opening leading east into a passageway.\n");

	DARK;

	EXIT(CAVE + "cave03", "east", 0, 0);

	reset_vin_mount_room();
}

void
call_goblin()
{
	if (!objectp(sgoblin))
		return;

	sgoblin->go_on_attack();
}