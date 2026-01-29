/*
 * Entrance of Dol Guldur - /d/Gondor/rhovanion/dolguldur/entrance.c
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
    
    set_short("Gates of Dol Guldur");
    set_long("You are standing in front of the gates of Dol Guldur, with " +
        "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " looking " +
        "down upon you. Much of the city appears to still be in ruins, " +
        "especially the jagged tower that rises up in the middle of town, " +
        "although the immediate area appears to have been restored " +
        "recently. An old highway, ancient and broken, runs through the " +
        "gate to the southwest, while a wide road continues into the " +
        "heart of the city to the northeast. A small lane follows the " +
        "southern wall east from here, while a narrow street hugs the " +
        "western wall as it moves off to the northwest. A very large " +
        "building rises up before you to the north, although you cannot " +
        "see an entrance from here.\n");

    add_item( ({"building", "large building"}),
        "This large building appears to be quite solidly built and well " +
        "maintained. There are some windows which overlook the gate, but " +
        "there is no entrance that you can see from here.\n");
    add_item( ({"highway", "old highway", "broken road", "ancient road",
            "broken highway", "ancient highway", "old road"}),
        "This road cuts a clear path through Mirkwood forest before " +
        "eventually finding the Anduin river.\n");
    add_item( ({"river", "anduin", "anduin river"}),
        "The Anduin river is not visible from here, but you could follow " +
        "the ancient highway through the gates here to find it.\n");
    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The thick wooden gates of Dol Guldur stand open, looking out " +
        "upon the ancient highway which dives through the black trees " +
        "of Mirkwood forest.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"narrow street", "street"}),
        "This narrow street wanders off to the northwest, following " +
        "the rebuilt walls of Dol Guldur. You notice several piles of " +
        "rotting garbage gathered along the wall.\n");
    add_item( ({"small lane", "lane"}),
        "You notice a small lane running east along the southern wall " +
        "of Dol Guldur, although most of it seems to be filled with " +
        "piles of garbage.\n");
    add_item( ({"wood", "beam", "wooden beam", "beams", "wooden beams"}),
        "Thick wooden beams have been used to make this gate very strong " +
        "and sturdy.\n");

    set_no_exit_msg( ({"north"}),
        "You cannot go that way, there appears to be a large building " +
        "blocking you!\n");
    set_no_exit_msg( ({"southeast", "south", "west"}),
        "The city wall rises up before you, preventing you from going " +
        "in that direction.\n");

    add_exit(DG_DIR + "main1", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "lane1", "east", 0, 3, 0);
    add_exit(DG_DIR + "path3", "southwest", 0, 3, 0);
    add_exit(DG_DIR + "street1", "northwest", 0, 3, 0);
}