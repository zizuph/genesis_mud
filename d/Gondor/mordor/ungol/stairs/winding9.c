/*
 * /d/Gondor/mordor/ungol/stairs/winding9.c
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
    make_the_room("There is a small overhanging shelf you can climb onto " +
        "from here.");

    add_item( ({ "shelf", "shelves", "overhanging shelf"}),
        BSN("From here you can see a small shelf higher up in the mountain, " +
        "though you cannot see what is on it from here."));

    add_exit(STAIRS_DIR + "winding8",  "west", 0,  5);
    add_exit(STAIRS_DIR + "ravine1",   "east", 0,  5);
    add_exit(STAIRS_DIR + "winding10", "up",   0, 10);
}
