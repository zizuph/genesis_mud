/* 
 * New cave expansion.
 *
 * Mortis 10.2006
 */

#include "../local.h";

inherit CAVE_BASE

void
create_vin_mount_room() 
{
	SHORT("T-passageway in a cave");
	LONG("The flicker of torchlight from the west barely illuminates "
	+ "this cramped, natural cave.  The passageway forms a 'T' here heading "
	+ "north into darkness, and from the east the foul stink of rot and "
	+ "refuse assault your senses.\n");

	EXIT(CAVE + "cave03", "north", 0, 0);
	EXIT(CAVE + "cave02", "east", 0, 0);
	EXIT(CAVE + "cave1", "west", 0, 0);
}
