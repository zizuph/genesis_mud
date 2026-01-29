/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

#define GOBLIN_ALCOVE			(CAVE + "cave04")

inherit CAVE_BASE

object sghome = find_object(GOBLIN_ALCOVE);

void
create_vin_mount_room() 
{
	SHORT("Passageway in a cave");
	LONG("Fragments of shattered stalagmites litter the floor of this "
	+ "cramped, natural passageway.  It continues north into the dark "
	+ "and south to what the flicker of torchlight reveals to be a 'T'.\n");

	ITEM(({"fragment", "fragments", "stalagmite", "stalagmites"}),
	  "Fragments of stalagmites, shattered by heavy blows, lay scattered "
	+ "haphazardly about the floor of this natural cave passageway.  One "
	+ "of the fragments is stuck in a crack in the western wall.\n");
	ITEM(({"flicker", "torchlight"}), "Your eyes barely detect the flicker "
	+ "of torchlight to the south.\n");
	ITEM("crack", "You spot a long crack in the western wall.  It seems to "
	+ "fold over an opening leading west into a perpendicular passageway.\n");

	DARK;

	GOBLIN_ALCOVE->teleledningsanka();

	EXIT(CAVE + "cave05", "north", 0, 0);
	EXIT(CAVE + "cave01", "south", 0, 0);
	add_invis_exit(CAVE + "cave04", "west", 0, 0);
}

void
enter_inv(object ob, object from)
{
	GOBLIN_ALCOVE->call_goblin();

	::enter_inv(ob, from);
}
