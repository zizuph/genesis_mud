/*
 * 	top3.c			Styles.   3 Mar 1993
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
    set_long("You are deep in the Grey Mountains, following a narrow " +
        "trail that cuts along the rugged slopes. Dozens of boulders " +
        "are lodged in the patches of tall grass and wildflowers that " +
        "cover the mountainside. Far off in the distance to the north, " +
        "you see a small stream falling over a tall mountain cliff, " +
        "displaying a beautiful waterfall that crashes down in " +
        "picturesque fashion. The slopes of the mountain are rather " +
        "steep and unstable here, and the only safe passage is to " +
        "follow the trail as it wraps around the mountain to the " +
        "south and east.\n");

    add_trees(0);

    add_exit(THIS_DIR + "top4","south");
    add_exit(THIS_DIR + "top2","east");
    add_exit(THIS_DIR + "top3","southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top3","west","@@mount@@",1,1);
    add_exit(THIS_DIR + "top3","northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top3","southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "top3","north","@@mount@@",1,1);
    add_exit(THIS_DIR + "top3","northeast","@@mount@@",1,1);

    add_item(({"waterfall","waterfalls","cliff","cliffs","tall cliff",
            "mountain cliff","tall mountain cliff","stream","small stream",
            "mountain stream","small mountain stream"}),
        "Far away from the trail to the north, you can see a small " +
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