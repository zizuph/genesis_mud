/*
 * /d/Gondor/mordor/ungol/stairs/ravine1.c
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
    set_long(BSN("You are in a long ravine between piers and columns of " +
        "torn and weathered rock, standing like huge unshapen statues on " +
        "either hand. To the east is a great upthrusting wall mass of " +
        "mountain-stone. Dark it looms, towering up high above you, " +
        "shutting out the view of all that lies beyond.")); 

    RAVINE;
    PIERS;
    FLOOR;
    add_item(({"wall","mountain","mountains","ephel duath"}), BSN(
    "Some way ahead and upwards, beyond the ravine, there is a great grey " +
    "wall, a last huge upthrusting mass of mountain-stone, looming dark above. " +
    "Above the wall, the crown of the moutain ridge is visible against the " +
    "sky."));
    add_item(({"crown","ridge","sky"}), BSN(
    "To the east, still high above, against the sky a cleft is outlined in the " +
    "topmost ridge, narrow, deep-cloven, between two black shoulders. And on " +
    "either shoulder is a horn of stone, peaks of the Ephel Duath."));

    add_exit(STAIRS_DIR + "winding9", "west",      0, 5);
    add_exit(STAIRS_DIR + "ravine2",  "east",      0, 2);
    add_exit(STAIRS_DIR + "hole1",    "north",     0, 2);
    add_exit(STAIRS_DIR + "hole3",    "southeast", 0, 2);
}
