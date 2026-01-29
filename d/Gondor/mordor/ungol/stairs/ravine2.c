/*
 * /d/Gondor/mordor/ungol/stairs/ravine2.c
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
    set_short("In a narrow ravine in the Ephel Duath");
    set_long(BSN("This is the middle of a long ravine between piers and columns of " +
        "torn and weathered rock. To the east is a great upthrusting wall mass of " +
        "mountain-stone. Dark it looms, towering up high above you, " +
        "shutting out the view of all that lies beyond."));

    RAVINE;
    PIERS;
    FLOOR;
    add_item(({"wall","mountain","rock"}), BSN(
        "The great grey wall looms dark above the ravine. It is a huge " +
        "upthrusting mass of mountain-stone, towering high above, shutting " +
        "out the view of all that lies beyond."));

    add_exit(STAIRS_DIR + "ravine3",  "east",  0, 2);
    add_exit(STAIRS_DIR + "hole4",    "south", 0, 2);
    add_exit(STAIRS_DIR + "ravine1",  "west",  0, 2);
}
