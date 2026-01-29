/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/main2.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

/*
 * Function name:        create_dg_room()
 * Description  :        Creates the dg from from the base file
 *                       /d/Gondor/rhovanion/dolguldur/std/base.c
 */
void 
create_dg_room()
{

    set_items_city();
    
    set_short("Dol Guldur");
    set_long("You are currently walking along the wide road which runs " +
        "through the middle of Dol Guldur. In the " + VBFC("daylight_desc") + 
        " you can see several groups of orcs sparring in a clearing " +
        "amongst the rubble just to the west. While to the east, an almost " +
        "constant parade of orcs are running in and out of a small shack. " +
        "The city gates of Dol Guldur are somewhere at the end of this " +
        "road to the southwest, while the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " illuminates a jagged and broken tower " +
        "which rises up to the northeast.\n");

    add_item( ({"guild", "adventurers guild", "clearing", "group",
            "groups", "sparring", "circle", "small circle"}),
        "You notice several groups of orcs sparring with weapons in a " +
        "small circle which has been cleared in the rubble west of here.\n");
    add_item( ({"post", "post office", "shack", "small shack"}),
        "There appears to be a small shack just east of you, where " +
        "you see several orcs running in and out of almost constantly.\n");
    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are at the end of this road to the " +
        "southwest.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "Just down the road to the northeast, you see this ruined tower " +
        "rising high above the rest of the city.\n");

    /* Some tells are duplicated to give a higher occurance rate */
    add_tell("A small orc enters the small shack at a dead run.\n");
    add_tell("A small orc leaves the small shack at a dead run.\n");
    add_tell("A small orc enters the small shack at a dead run.\n");
    add_tell("A small orc leaves the small shack at a dead run.\n");
    add_tell("A small orc enters the small shack at a dead run.\n");
    add_tell("A small orc leaves the small shack at a dead run.\n");
    add_tell("A small orc enters the small shack at a dead run.\n");
    add_tell("A small orc leaves the small shack at a dead run.\n");
    add_tell("A band of orcs wander into the clearing to the west.\n");
    add_tell("A lone orc wanders out from the clearing clutching a " +
        "bleeding wound on his arm before trotting away to the " +
        "southwest.\n");

    set_no_exit_msg( ({"north", "southeast", "south", "northwest"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");

    add_exit(DG_DIR + "main3", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "post", "east", 0, 3, 0);
    add_exit(DG_DIR + "main1", "southwest", 0, 3, 0);
    add_exit(DG_DIR + "adv", "west", 0, 3, 0);
}