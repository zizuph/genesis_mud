/*
 * /d/Gondor/mordor/ungol/stairs/winding7.c
 *
 * This the a room on the Winding Stair. These rooms are very easy with all
 * kinds of fancy stuff in the default.
 *
 * /Mercade, 23 November 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_winding";

#include "/d/Gondor/defs.h"
#include "stairs.h"

void
create_room()
{
    set_red_light(1); /* This call should be before make_the_room. */
    make_the_room("Here you see a flight leading up.");

    add_item( ({ "flight", "stair" }),
        BSN("It is a flight, short and straight, climbing out on to another " +
        "level."));

    add_exit(STAIRS_DIR + "winding6", "west", 0,  5);
    add_exit(STAIRS_DIR + "winding8", "up",   0, 10);
}
