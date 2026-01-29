/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(CLEARING);

    set_long_desc("The lush undergrowth of the forest forms a living " +
		  "boundary around its edges. In the center of the " +
		  "clearing is a huge vallenwood. A stairway spirals " +
		  "down around the trunk, reaching the ground right " +
		  "before you. To the north is the East road.");

    add_exit(TDIR + "east_road2", "north");
    add_exit(TDIR + "platform3", "up");
}


