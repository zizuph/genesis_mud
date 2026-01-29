/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";

inherit CAVE_BASE

void
create_vin_mount_room() 
{
	SHORT("Refuse pile in a cave");
	LONG("The few stalagmites here that are not broken protrude through "
	+ "through heaps of refuse, bone, and vermin.  The stalactites above "
	+ "are stained brownish-black and dripping with filth.  The smell in "
	+ "this cramped, natural cave is overpoweringly rotten and wafts on "
	+ "waves of sickening heat coming off the piles.\n");

	ITEM(({"heap", "heaps", "pile", "piles", "refuse", "bone", "vermin",
	"trash"}), "Heaps of refuse, clumps of feces, broken and gnawed bones, "
	+ "and a variety of foul trash rise knee deep in this cramped cave "
	+ "swallowing the broken stalagmites and most of the ones still intact.  "
	+ "It reeks of rot and poorly digested crap, and you're confident it is "
	+ "crawling with vermin.\n");
	ITEM(({"stalagmite", "stalagmites"}), "Most of the stalagmites on the "
	+ "floor are broken and buried by trash.  The tops of a few poke through "
	+ "the knee deep refuse filling the cave.\n");
	ITEM(({"stalactite", "stalactites", "ceiling"}), "Long stalactites hang "
	+ "down from the ceiling around a small opening.  They have been stained "
	+ "brownish-black from filth and occasionally drip with rot and "
	+ "moisture.\n");
	ITEM("filth", "Brownish-black and green filth stain the stalactites "
	+ "overhead as if it were poured down on them from above.\n");
	ITEM("opening", "A small, oval opening is recessed into the darkness of "
	+ "the ceiling among the stained stalactites.  There is no way to climb "
	+ "through the refuse, slick stalactites, or walls to reach it.\n");

	DARK;

	EXIT(CAVE + "cave01", "west", 0, 0);
}
