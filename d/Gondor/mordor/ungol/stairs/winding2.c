/*
 * /d/Gondor/mordor/ungol/stairs/winding2.c
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
    set_red_light(1); /* This call should be before make_the_room */
    make_the_room();

    add_exit(STAIRS_DIR + "winding1", "west",      0, 5);
    add_exit(STAIRS_DIR + "winding3", "northeast", 0, 5);
}
