/*
 * 	gravel.c			Styles.   3 Mar 1993
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
    set_herbs();

    set_short("Gravel slope");
    set_long("You are standing on a gravel slope in the foothills of the " +
        "Grey Mountains. To the north, a grassy hill rises up with a " +
        "magnificent garden enhanced by the immaculate green lawn which " +
        "sits around it. Dominating your view to the west and south, " +
        "the snow-capped peaks of the Grey Mountains reach up into the " +
        "blue sky above, surrounding the valley that stretches out across " +
        "the northeastern horizon. Fields of tall green grasses and " +
        "brightly coloured wildflowers spread out around you, occasionally " +
        "broken by the occasional grove of trees. A narrow trail " +
        "winds up the gravel slope to the west, climbing deeper " +
        "into rugged depths of the mountains.\n");

    add_trees(0);

    add_exit(THIS_DIR + "lawn","north");
    add_exit(THIS_DIR + "top1","west");

    set_no_exit_msg(({"southwest","southeast","south"}),
        "The mountains are simply too difficult to climb in that " +
        "direction, you will have to find another way around.\n");
    set_no_exit_msg(({"northwest","northeast","east"}),
        "As you start to make your way into the foothills, you notice " +
        "that the land is unstable, making a landslide a realistic " +
        "danger! You will have to make your way back to the path.\n");

    add_item(({"garden","magnificent garden"}),
        "You are not close enough to see many details, but even from " +
        "this distance, the garden looks magnificent.\n");
    add_item(({"lawn","green lawn"}),
        "It seems rather strange to see such a well maintained lawn " +
        "and garden alone in the foothills of these mountains. There " +
        "is probably some reason for it, but you won't figure it out " +
        "from here!\n");
    add_item(({"trail","narrow trail","gravel trail","dirt trail","path",
            "narrow path","gravel path","dirt path"}),
        "This trail is mostly dirt, as it winds a safe path through " +
        "the loose gravel that covers the slope before you. The climb " +
        "west looks pretty steep, but managable if you stay on the path.\n");
    add_item(({"slope","steep slope","mountain slope","foothill","gravel",
            "gravel slope"}),
        "The Grey Mountains rise up directly before you to the west, " +
        "in particular, a rocky slope full of loose gravel. A narrow " +
        "trail cuts through the gravel, providing passage up the slope " +
        "and deeper into the mountains.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest","south",
            "southern horizon","south horizon","western horizon","west",
            "west horizon"}),
        "The Grey Mountains loom high above you in that direction, " +
        "preventing you from seeing much of the horizon.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}