/*
 * 	s_road2.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

/* prototypes */
public int        block_exit();

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_brightroad();
    set_herbs();

    set_short("Bright road");
    set_long("You on the southern side of an old stone bridge that allow " +
      "the Bright Road to cross over the rocky ravine of the Copper River. " +
      "The highway continues to run north past the bridge, in the general " +
      "direction of Sparkle, whose wooden walls are barely visible against " +
      "the backdrop of the Pen Sea on the northeastern horizon. Grassy " +
      "fields full of wildflowers melt into the dark shadows of the " +
      "Jade Forest which loom over the road, while rugged foothills " +
      "rise up switfly into the rocky peaks known as the Grey Mountains " +
      "which dominate the view to the west. The Bright Road itself " +
      "continues to run in a straight line north and south, broken only " +
      "by a small dirt path that intersects it and follows the Copper " +
      "River to the east and west.\n");

    add_trees(1);

    add_exit(THIS_DIR + "s_road2a","north");
    add_exit(THIS_DIR + "s_road3a","south");
    add_exit(THIS_DIR + "stream2", "east", block_exit, 1, 0);
    add_exit("/d/Sparkle/guilds/monks/meadows/room/meadows_3", "west");

    set_no_exit_msg(({"northeast","northwest"}),
        "The ravine that dives steeply down towards the river looks too " +
        "dangerous for you to climb down!\n\n"+
        "You are unable to go in that direction!\n");
    set_no_exit_msg(({"southwest"}),
        "The foothills are far too treacherous and difficult to climb " +
        "here, it looks like you will have to follow the Bright Road " +
        "instead.\n");
    set_no_exit_msg(({"southeast"}),
        "The dark shadows of the Jade Forest loom above you directly to " +
        "southeast. Taking a quick glance, you decide that this is probably " +
        "not the best place, or time, to enter them.\n");

    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Copper River just north " +
        "of you.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "To the northeast of you here, the wooden stockade which " +
        "surrounds the city of Sparkle is barely visible against the blue " +
        "waters of the Pen Sea that spreads across the horizon beyond.\n");
    add_item(({"sparkle","city","town","village","port"}),
        "The city of Sparkle, widely hailed as the greatest port in the " +
        "world, lies somewhere on the other side of the Copper River.\n");
    add_item(({"wall", "walls", "wood wall", "wooden walls",
            "sparkle wall", "sparkle walls","stockade","wooden stockade"}),
        "You cannot really make out the walls very well at this " +
        "distance, but you know them to be tall and stron.\n");
    add_item(({"hill","foothill","foothills","hills","rugged foothills",
            "rugged hills","rugged foothill","rugged hill"}),
        "Broken land rises up before you to the west as rugged " +
        "foothills transform into the jagged and rocky peaks of the " +
        "Grey Mountains.\n");
    add_item(({"copper river"}),
        "Rushing before you in a violent storm is the Copper River, " +
        "crashing down from the heights of the Grey Mountains before " +
        "it meets up with the Diamond River and empties out into the " +
        "Pen Sea.\n");
    add_item(({"bridge","old bridge","old stone bridge","stone bridge"}),
        "This old bridge has been made from the same white stone as " +
        "the rest of the highway. It seems to be in exceptionally good " +
        "shape as it crosses over the tumbling waters of the Copper " +
        "River below.\n");
    add_item(({"path","dirt path","small dirt path","small path","trail",
            "small dirt trail","small trail","dirt trail","intersection"}),
        "This small dirt path winds down out of the mountains, following " +
        "the Copper River intersecting the Bright Road and continuing " +
        "east towards the Pen Sea.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 
 * Function name:        block_exit
 * Description  :        make it so that players are not allowed to
 *                       use this exit
 * Returns      :        int 1 (always)
 */
public int
block_exit()
{
    write("As you try to proceed along the trail a group of Mercenaries"
        + " appear and usher you back the the road saying, \"We don't even"
        + " allow our own members to use this trail. If you want to find"
        + " the Mercenary Camp, you will need to go through Sparkle and"
        + " approach from that route.\"\n");

    return 1;
} 
/* block_exit */
