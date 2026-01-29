/*
 *  /d/Genesis/start/human/wild2/orc_road2b.c
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
    set_long("You are just east of the High Pass, on the western edge of " +
        "Sparkle valley. The tall, snow-capped peaks of the Grey Mountains " +
        "surround you here, with the flat stones of the Orc Road diving " +
        "directly west into them. To the east, the mountains slowly " +
        "fall down into rocky foothills coming to eventually rest against " +
        "the shores of the great blue ocean known as the Pen Sea. Several " +
        "small fields and meadows, covered in tall grasses and wildflowers, " +
        "lay hidden amongst the foothills here, but the only safe " +
        "passage seems to be found by following the highway to the " +
        "east or west.\n");

    add_trees(0);

    add_exit(THIS_DIR + "orc_road2c","west","@@pass@@");
    add_exit(THIS_DIR + "orc_road2a","east");
    add_exit(THIS_DIR + "orc_road2b", "southwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2b", "northwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2b", "north", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2b", "northeast", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2b", "south", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "orc_road2b", "southeast", "@@mount@@", 1,1);

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
 * Function name:        pass
 * Description  :        Provides some atmosphere by giving an echo as the 
 *                       player walks through the High Pass.
 * Returns      :        int 0 - allows the player to move along the exit path
 */
int
pass()
{
    write("You climb up and over the High Pass.\n");
    return 0;
}
/* pass */
