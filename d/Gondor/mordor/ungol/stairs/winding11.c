/*
 * /d/Gondor/mordor/ungol/stairs/winding10.c
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
    set_red_light(2); /* This call should be before make_the_room. */
    make_the_room("The shelf you are on continues to the east.");

    set_short("On a small shelf in the Mountains of Shadow");

    add_exit(STAIRS_DIR + "winding10", "east", 0, 5);
}
