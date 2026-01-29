/*
 * /d/Gondor/mordor/ungol/stairs/ravine3.c
 *
 * Olorin, 21 December 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "ravine.h"

void
create_room()
{
    set_short("At the opening of a cave, the entrance to Torech Ungol");
    set_long(BSN("This is the end of a long ravine between piers and columns of " +
        "torn and weathered rock. To the east is a great upthrusting wall mass of " +
        "mountain-stone. Dark it looms, towering up high above you, " +
        "shutting out the view of all that lies beyond. " +
        "In the midst of it there is the opening of a cave.")); 

    RAVINE;
    PIERS;
    FLOOR;
    add_item(({"wall","mountain","rock"}), BSN(
        "The great grey wall looms dark above the ravine. It is a huge " +
        "upthrusting mass of mountain-stone, towering high above, shutting " +
        "out the view of all that lies beyond. In its midst there is the " +
        "dark opening of a cave."));
    add_item( ({ "opening", "entrance", "cave", "torech ungol" }),
        BSN("Peering into the gloom you cannot see anything but the " +
        "entrance to a dark cave. A terrible smell comes from the opening " +
        "of it and you wonder how much worse it gets once you enter it."));


    add_exit(LAIR_DIR   + "tunnel1",  "east", 0, 5);
    add_exit(STAIRS_DIR + "ravine2",  "west",  0, 2);
    add_exit(STAIRS_DIR + "hole6",    "north", 0, 2);
    add_exit(STAIRS_DIR + "hole8",    "south", 0, 2);
}
