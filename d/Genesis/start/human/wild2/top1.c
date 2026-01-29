/*
 * 	top1.c			Styles.   3 Mar 1993
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
    set_items_mountain();

    set_short("Top of trail");
    set_long("You are at the top of a narrow trail that has cut deep " +
        "into the Grey Mountains. The slopes of the mountains are mostly " +
        "filled with patches of green grass, with clusters of wildflowers " +
        "sprinkled in for colour. You also notice the occasional grove " +
        "of trees hiding behind the dozens of rocks and boulders that " +
        "are scattered all around you here, while off in the distance you " +
        "are able to see the a small mountain stream cascading " +
        "in a picturesque waterfall. The trail you are on falls " +
        "down a steep gravel slope to the east, while continuing on " +
        "southwards along the steep mountainside.\n");

    add_trees(1);

    add_exit(THIS_DIR + "top2","south");
    add_exit(THIS_DIR + "gravel","east");

    set_no_exit_msg(({"southwest","north","southeast","west","northwest",
            "northeast"}),
        "The mountains are simply too dangerous to climb in that " +
        "direction, you will have to find another way around.\n");

    add_item(({"waterfall","waterfalls","cliff","cliffs","tall cliff",
            "mountain cliff","tall mountain cliff","stream","small stream",
            "mountain stream","small mountain stream"}),
        "Far away from the trail to the west, you can see a small " +
        "stream dropping off a mountain cliff in a spectacular looking " +
        "waterfall.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}