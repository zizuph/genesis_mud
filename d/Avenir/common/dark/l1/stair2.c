// stair2
// connecting L1/stair1 with Terel/dark/w4.c
/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public int
noise_down(void)
{
    write("You drop down into the pit...\n");
    return 0;
}

public void
create_room(void)
{
    set_short("Cave");
    set_long("Something about this place makes your hackles " +
	     "rise. Perhaps it is the odd absence of the moss and " +
	     "fungi present in the tunnel beyond, or the eerie " +
	     "sounds made by the wind that rushes upward from " +
	     "the hole in the cave's center. Light is reflected by " +
	     "the myriad miniature crystals embedded in the rough " +
	     "stone walls, irritating your eyes with the glare.\n");

    add_item(({"crystals", "crystal"}),
	"The crystals are tiny and of no value.\n");
    add_item(({"stone", "living stone", "walls", "wall"}),
	"The walls appear to have been cut by hands skilled in " +
	"working with stone.\n");
    add_item(({"hole", "pit"}),
	"It is impossible to gauge its depth.\n");

    IN; BLACK; NO_STEED;

    add_exit(L1 + "stair1", "down", noise_down);
    add_exit(L1 + "w4", "northeast");
}
