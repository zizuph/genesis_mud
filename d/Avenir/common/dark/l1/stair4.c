// file name: /d/Avenir/common/dark/l1/stair4
// revision history: Denis, Apr 96, Added notifying statserv when someone enters
//                                  utterdark through this room.
//
/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("stair");
    set_long("An elaborate stairway has been carved from out " +
	     "of living stone.  It appears to be worn smooth by the " +
	     "passage of many feet. Veins of semi-precious stone " +
	     "flow along the walls like rivers of carnelian blood.\n");

    add_item("carnelian", "A red semi-precious stone. It occurs in " +
	     "veins in this tunnel area.\n");
    add_item(({"stone", "living stone", "walls", "wall"}),
	"The walls appear to have been cut by hands skilled in " +
	"working with stone.\n");

    IN; BLACKER; NO_STEED;

    add_exit(L1 + "ne1", "up");
    add_exit(L3 + "e2", "down");
    add_exit(L1 + "lair", "north");
}
