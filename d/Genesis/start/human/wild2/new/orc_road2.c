/*
 * 	orc_road2.c			Styles.   3 Mar 1993
 *
 * Updated by Varian, March 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_orcroad();
    set_herbs();

    set_short("Orc road");
    set_long("You are walking along the Orc Road as it cuts through " +
        "Sparkle valley on its way west towards the High Pass. The " +
        "highway climbs through narrow fields of tall grasses and " +
        "colourful wildflowers. Just beyond the fields, a jumbled " +
        "mass of rocky foothills leap up, growing into the jagged peaks " +
        "of the Grey Mountains. Several trees grow near the road as " +
        "it runs from the distant city of Sparkle, barely visible on " +
        "the eastern horizon, towards the High Pass through the " +
        "mountains to the west.\n");

    add_trees(0);

    add_exit(THIS_DIR + "orc_road2a","west");
    add_exit(THIS_DIR + "orc_road1","east");
    add_exit(THIS_DIR + "orc_road2", "southwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2", "northwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2", "north", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2", "northeast", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2", "south", "@@rough@@", 1,1);
    add_exit(THIS_DIR + "orc_road2", "southeast", "@@rough@@", 1,1);

    add_item(({"foothill","foothills","rock","rocks","rocky foothill",
            "rocky foothills","rugged foothill","rugged foothills"}),
        "The land both north and south of the road quickly becomes " +
        "rocky and broken as the rugged foothills quickly transform " +
        "themselves into the Grey Mountains.\n");
    add_item(({"mountain","mountains","grey mountains","grey mountain",
            "peak","peaks","jagged peak","jagged peaks"}),
        "The jagged peaks of the Grey Mountains surround the valley " +
        "around you here, with the only easy passage being east " +
        "down into the valley or west through the High Pass.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
mount()
{
    write("The mountains here look far too difficult for you to climb! You " +
        "will have to find another way around them.\n");
    return 1;
}
/* mount */

/*
 * Function name:        rough
 * Description  :        Gives an explanation for why the mortal cannot travel
                         in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
rough()
{
    write("The foothills are a little bit too rough for you to make any " +
        "progress in that direction. It looks like you will have to " +
        "follow the Orc Road for now.\n");
    return 1;
}
/* rough */