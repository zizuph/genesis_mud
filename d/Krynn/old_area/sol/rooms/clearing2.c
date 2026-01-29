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
		  "before you. The east you can see yet another clearing, " +
		  "it is the Solace square.");

    add_exit(TDIR + "square", "east");
    add_exit(TDIR + "platform4", "up");
}


