/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/main1.c
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
    set_long("The " + VBFC("daylight_desc") + " looks down upon you as you " +
        "wander along the long, wide road which runs through the middle " +
        "of Dol Guldur. A tall tower, still jagged and broken, stands " +
        "in the distance to the northeast and the stout city gates are " +
        "clearly visible a short distance to the southwest. While much of " +
        "Dol Guldur is still in ruins, this part of the city seems to have " +
        "been mostly restored. An open doorway leads into the large " +
        "building that stands just west of here, while it appears that " +
        "a small shop is just east of you.\n");

    add_item( ({"building", "large building"}),
        "This large building appears to be quite solidly built and well " +
        "maintained. An open doorway seems to invite you to enter.\n");
    add_item( ({"shop", "small shop", "store"}),
        "It appears that some enterprising individual has set up shop " +
        "in the restored part of Dol Guldur.\n");
    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are nearby, at the end of this road " +
        "to the southwest.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "In the distance to the northeast, you see this ruined tower " +
        "rising high above the rest of the city.\n");

    add_tell("A heavily armed orc wanders into the large building to " +
        "west.\n");
    add_tell("You hear heated voices arguing as they barter in the " +
        "small shop just east of here.\n");

    set_no_exit_msg( ({"north", "southeast", "south", "northwest"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");

    add_exit(DG_DIR + "main2", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "shop", "east", 0, 3, 0);
    add_exit(DG_DIR + "entrance", "southwest", 0, 3, 0);
    add_exit(DG_DIR + "barracks", "west", "@@barracks@@", 3, 0);
}

int
barracks()
{
    write("You attempt to enter the barracks, but an Easterling " +
        "soldier stops you and informs you that the officers are " +
        "busy in a meeting. You will have to come back at " +
        "another time.\n");
    return 1;
}