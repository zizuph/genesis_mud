/*
 * 	top4.c			Styles.   3 Mar 1993
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
    set_long("You are high up in the Grey Mountains, walking along a " +
        "narrow trail that winds a path across the steep slopes. Dozens " +
        "of rocks and boulders litter the mountainside, hiding amongst " +
        "the tall grasses and wildflowers that grow up here. A rough " +
        "hole appears to open up into the side of the mountain here, " +
        "falling down into a deep cave to the east. While the trail " +
        "you are on continues to provide safe passage across the " +
        "mountain slopes to both the north and the west.\n");

    add_trees(0);

    add_exit(THIS_DIR + "top3","north");
    add_exit(THIS_DIR + "top5","west");
    add_exit("/d/Shire/clubs/sgc/jcave", "east");
    add_exit(THIS_DIR + "top4","southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top4","northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "top4","southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "top4","south","@@mount@@",1,1);
    add_exit(THIS_DIR + "top4","northeast","@@mount@@",1,1);

    add_item(({"cave","cave opening","opening","hole","rough hole"}),
        "A rough hole in the side of the mountain opens up into " +
        "what appears to be a fairly deep cave.\n\nWhat could be " +
        "inside???\n");

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
    write("The mountains are simply too difficult to climb in that " +
        "direction, you will have to find another way around.\n");
    return 1;
}
/* mount */