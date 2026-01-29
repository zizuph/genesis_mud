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

    set_long_desc("This clearing is set off from the West road. The " +
		  "lush undergrowth of the forest forms a living " +
		  "boundary around its edges. In the center of the " +
		  "clearing is a huge vallenwood. A stairway spirals " +
		  "down around the trunk, reaching the ground right " +
		  "before you. The West road is visible to your north.");

    add_item(({"undergrowth","lush undergrowth"}),"The undergrowth " +
        "is thick, and prevents movement in all directions except " +
        "north.\n");
    add_item("forest","The forest surrounds you on all sides, except " +
        "to the north, where it opens up into the ground level of " +
        "the village of Solace.\n");

    add_exit(TDIR + "west_road4", "north");
    add_exit(TDIR + "platform7", "up");
}


