/*
 * 	big_tree.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

void
create_wild_room()
{
    set_items_sparkle();
    set_herbs();

    set_short("Under a MASSIVE oak tree");
    set_long("You are walking along a small dirt path that cuts through " +
        "the rugged foothills of the Grey Mountains. A massive oak tree " +
        "grows here, straining to reach up towards the sky and casting " +
        "shade on the ground below. Rocky cliff walls and large boulders " +
        "seem to surround you on all sides here, surrounding you with an " +
        "uneasy feeling of being trapped. Looking around, it appears " +
        "that the only way out from here is to follow the trail deeper " +
        "into the rugged mountains to the west or out towards the " +
        "grassy fields of the valley to the east.\n");

    add_trees(0);

    add_exit(THIS_DIR + "grove","west");
    add_exit(THIS_DIR + "field8","east");
    add_exit(THIS_DIR + "big_tree", "southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "big_tree", "south","@@mount@@",1,1);
    add_exit(THIS_DIR + "big_tree", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "big_tree", "north","@@mount@@",1,1);
    add_exit(THIS_DIR + "big_tree", "northeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "big_tree", "northwest","@@mount@@",1,1);

    add_item(({"woodwork","wood"}),
        "You really cannot tell what this is from down here, and " +
        "it does not seem like you are able to climb this tree. This " +
        "feels like a mystery destined to remain unsolved.\n");
    add_item(({"rock","rocks","cliff","rocky cliff","cliffs","rocky cliffs",
                "steep cliff","steep cliffs","wall","walls","cliff wall",
                "cliff walls","rocky cliff wall","rocky cliff walls"}),
        "The rocky cliffs that surround you to the north and south are" +
        "almost certainly too high and dangerous to climb. You strongly " +
        "suspect that the only way out from here is to follow the " +
        "path east or west.\n");
    add_item(({"foothill","foothills","rugged foothills","rugged foothill"}),
        "You are in the foothills of the Grey Mountains beneath a " +
        "massive oak tree. Steep cliff walls of rock surround you " +
        "on either side of the path, fading away as they approach " +
        "the valley to the east.\n");
    add_item(({"tree","oak","oak tree","massive tree","massive oak",
                "massive oak tree"}),
        "It would take at least 3 men or 15 dwarves to embrace it.\n"+
        "Something, maybe woodwork of some kind, can be seen up there\n"+
        "if you strain your eyes to see. However, the tree might be\n"+
        "difficult to climb...\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "This small dirt path seems to wind deeper into the " +
        "mountains to the west while also providing access to " +
        "the valley in the east.\n");
    add_item(({"horizon"}),
        "You are too deep in the mountains to see much of any horizon " +
        "save to the east.\n");
    add_item(({"north horizon","northern horizon","north","northeast horizon",
            "northeastern horizon","northeast","northwest horizon",
            "northwestern horizon","northwest","south horizon",
            "southern horizon","south","southeast horizon",
            "southeastern horizon","southeast","southwest horizon",
            "southwestern horizon","southwest"}),
        "You try to look at the horizon in the distance, but (of course) " +
        "you can only see a big slab of rocky cliff here.\n");
    add_item(({"west horizon","western horizon","west"}),
        "Looking to the west, you really cannot see much more than a " +
        "grove of trees and a lot of mountains.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Looking to the east, you can see the path open out into a large " +
        "valley filled with grassy fields.\n");
    add_item(({"grove","grove of trees","groves","trees"}),
        "You cannot really see much from here, but there appears to be a " +
        "grove of trees growing near the path just west of here.\n");
    add_item(({"ground","down"}),
        "There are thick grasses filled with dozens of colourful " +
        "wildflowers growing beside the path here.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    add_cmd_item( ({ "oak", "tree", "oak tree" }), "climb", "@@climb" );

}

/*
 * Function name:        climb
 * Description  :        Provides an explanation why a mortal cannot climb
 */
string
climb(string str)
{
    return "You don't have what it takes to do that.\n";
}
/* climb */

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("The rocky cliffs here are far too rugged and difficult for you " +
        "to climb. You will have to find a path in a different direction.\n");
    return 1;
}
/* mount */