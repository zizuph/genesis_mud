// file name:        /d/Avenir/common/dark/l1 stair1
// revision history: Denis, Apr 96: Added notifying statserv when someone enters
//                                  utterdark through this room.
// purpose:          connecting L1/stair2 with L2/w6
/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public int
noise_up(void)
{
    write("Your muscles strain to pull you upward as you struggle " +
	  "to maintain your hand-holds.\n");
    return 0;
}

public int
noise_east(void)
{
    write("Grasping the beslimed edges of the hole, you hoist " +
	  "yourself through it.\n");
    return 0;
}

public void
create_room(void)
{
    set_short("Pit");
    set_long("A shallow pit through which wind howls, making " +
	     "your hackles rise.  Light sparkles off of crystals in the " +
	     "ceiling of the cave above.  To the east there is an " +
	     "opening in the wall at about chest height.\n");

    add_item("carnelian", "A red semi-precious stone. It occurs in " +
	"veins in this tunnel area.\n");
    add_item(({"stone", "living stone", "walls", "wall", "pit", "hole"}),
	"From the walls of this hole one might deduce that it had " +
	"been worn into the stone by water.\n");
    add_item(({"crystals", "crystal"}), "The crystals are high in " +
	     "the ceiling of the cave above and reflect the light.\n");

    IN; BLACKER; NO_STEED;

    add_exit(L1 + "stair2", "up", noise_up);
    add_exit(L2 + "w6", "east", noise_east);
}
