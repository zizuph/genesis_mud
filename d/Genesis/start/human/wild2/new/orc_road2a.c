/*
 *  /d/Genesis/start/human/wild2/orc_road2a.c
 *
 *      Hastily constructed road to assist with making Styles'
 *      maps accurate. (Gorboth)
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
    set_long("You are walking along the flat stones of the highway known " +
        "as the Orc Road. To the west, the High Pass though the mountains " +
        "is clearly visible, while a large green valley spreads out before " +
        "you to the east. Green grassy fields, filled with groves of trees " +
        "and sprinkled with colourful wildflowers, cover the foothills " +
        "before spreading out into the rest of the valley. Farther beyond, " +
        "the wide blue expanse of the Pen Sea is barely visible on " +
        "the eastern horizon. The Orc Road runs east and west along the " +
        "valley, with the rocky walls of the Grey Mountains reaching " +
        "for the sky on either side. \n");

    add_trees(0);

    add_exit(THIS_DIR + "orc_road2b","west");
    add_exit(THIS_DIR + "orc_road2","east");
    add_exit(THIS_DIR + "orc_road2a", "southwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2a", "northwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2a", "north", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2a", "northeast", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2a", "south", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2a", "southeast", "@@rough@@", 1,1);

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