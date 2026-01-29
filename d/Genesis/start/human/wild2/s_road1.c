/*
 * Creator: Shadowlynx
 * Date   : 15-Nov-2000
 * File   : /d/Genesis/start/human/wild2/s_road1.c
 * Purpose: Follows the stream near Sparkle to the Travellers Guild.
 * Modify : Modified from the original file created by Styles 3-Mar-1993.
 * Updates:
 *
 *  Modified - Varian  March, 2016
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
    set_items_brightroad();
    set_herbs();

    set_short("Bright road");
    set_long("A wide highway of large white stones runs in a straight line " +
        "to the north and south beneath your feet here. To the west, the " +
        "rugged foothills of the Grey Mountains quickly jump up and grow " +
        "into the jagged peaks that dominate the western horizon. On the " +
        "east side of the road, grassy fields full of wildflowers drops " +
        "down into the steep ravine of the Diamond River that rushes " +
        "and tumbles past below you. In the distance to the south, you can " +
        "make out the tall trees of the Jade Forest as they huddle over " +
        "the white line of the highway that cuts through it. Looking to " +
        "the northeast, you spot the wooden stockade that surrounds Sparkle " +
        "nestled securely against the shores of the Pen Sea.\n");

    add_trees(1);

    add_exit(THIS_DIR + "s_road1a","north");
    add_exit(THIS_DIR + "s_road2a","south");

    set_no_exit_msg(({"northeast","east","southeast"}),
        "The ravine that dives steeply down towards the river looks too " +
        "dangerous for you to climb down!\n\n"+
        "You are unable to go in that direction!\n");
    set_no_exit_msg(({"southwest","northwest","west"}),
        "The foothills are far too treacherous and difficult to climb " +
        "here, it looks like you will have to follow the Bright Road " +
        "instead.\n");

    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Bright Road here.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "To the northeast of you here, the wooden stockade which " +
        "surrounds the city of Sparkle stands out against the blue " +
        "waters of the Pen Sea that spreads across the horizon beyond.\n");
    add_item(({"sparkle","city","town","village","port"}),
        "The city of Sparkle, widely hailed as the greatest port in the " +
        "world, lies on the other side of the Diamond River.\n");
    add_item(({"wall", "walls", "wood wall", "wooden walls",
            "sparkle wall", "sparkle walls","stockade","wooden stockade"}),
        "A tall wooden wall graces the eastern horizon, surrounding the " +
        "legendary city of Sparkle.\n");
    add_item(({"hill","foothill","foothills","hills","rugged foothills",
            "rugged hills","rugged foothill","rugged hill"}),
        "Broken land rises up before you to the west as rugged " +
        "foothills transform into the jagged and rocky peaks of the " +
        "Grey Mountains.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}