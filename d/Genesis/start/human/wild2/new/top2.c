/*
 * 	top2.c			Styles.   3 Mar 1993
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

    set_short("Grey Mountains");
    set_long("You are walking along a narrow dirt trail that cuts " +
        "across the rugged slopes of the Grey Mountains. High above, " +
        "the jagged snow-capped peaks claw against the blue sky, " +
        "obscuring the horizon in every direction. The mountainsides " +
        "are mostly covered with a beautiful array of wildflowers that " +
        "hide behind patches of tall green grass. Dozens of rocks and " +
        "boulders are lodged on the slopes, often nestled behind " +
        "the occasional groves of trees. Off in the distance to the " +
        "northwest, you see a picturesque waterfall dropping over a tall " +
        "mountain cliff into the valley below. Since your footing up here " +
        "is somewhat treacherous, it is probably best to stick to the " +
        "trail as it follows the mountainside to the north and to " +
        "the west.\n");

    add_trees(0);

    add_exit(THIS_DIR + "top1","north");
    add_exit(THIS_DIR + "top3","west");
    add_exit(THIS_DIR + "top2","southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top2","south","@@mount@@",1,1);
    add_exit(THIS_DIR + "top2","northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top2","southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "top2","east","@@mount@@",1,1);
    add_exit(THIS_DIR + "top2","northeast","@@mount@@",1,1);

    add_item(({"waterfall","waterfalls","cliff","cliffs","tall cliff",
            "mountain cliff","tall mountain cliff","stream","small stream",
            "mountain stream","small mountain stream"}),
        "Far away from the trail to the northwest, you can see a small " +
        "stream dropping off a mountain cliff in a spectacular looking " +
        "waterfall.\n");

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
    write("The mountains are simply too dangerous to climb in that " +
        "direction, you will have to find another way around.\n");
    return 1;
}
/* mount */