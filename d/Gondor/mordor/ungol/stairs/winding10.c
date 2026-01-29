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
    make_the_room("You are on a small shelf that continues to the west. " +
        "Even from this higher place you do not have a good look over the " +
        "ravine for the dark clouds block most of the light.");

    set_short("On a small shelf in Ephel Duath");

    add_item(({"shelf","plateau"}), BSN(
        "This shelf of black stone is more or less level, allowing you to " +
        "continue west along your arduous trek. As you peer at the stone, " +
        "the shadows seem to gather at the periphery of your vision."));
    add_item(({"ravine",}), BSN(
        "Dimly you can make out tall piers and jagged pinnacles of stone " +
        "on either side, between which are great crevices and fissures blacker " +
        "than than the night. The main path running uphill in the bottom " +
        "of the ravine is hidden in black shadows."));
    add_item(({"path", "shadows", }), BSN(
        "Hidden in black shadows a path is running through the ravine further "
      + "eastwards."));
    add_exit(STAIRS_DIR + "winding9",  "down", 0, 10);
    add_exit(STAIRS_DIR + "winding11", "west", 0,  5);
}
