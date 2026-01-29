// file name: /d/Avenir/common/dark/l1/stair3
// creator(s):
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
    set_short("Stair");
    set_long("A crude stairway has been carved into the " +
	     "coarse black rock. The steps appear to have been " +
	     "polished by the passage of many feet. Pale red stone " +
	     "threads the walls in thin spidery veins.\n");

    add_item("carnelian", "A red semi-precious stone. It occurs in " +
	     "veins in this tunnel area.\n");
    add_item(({"stone", "living stone", "walls", "wall"}),
	"The walls appear to have been cut by hands skilled in " +
	"working with stone.\n");

    IN; BLACK;

    add_exit(L2 + "e9", "down");
    add_exit(L1 + "ne2", "southwest");
}
