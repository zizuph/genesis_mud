/*
 *  /d/Genesis/start/human/wild2/s_road2a.c
 *
 *      Hastily constructed road to assist with making Styles'
 *      maps accurate. (Gorboth)
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
    set_long("You are travelling along the Bright Road, a highway built " +
        "of brilliant white stones that runs south from Sparkle towards " +
        "the Jade Forest. Small patches of grassy fields filled with " +
        "bright wildflowers grow on either side of the road, before " +
        "falling away into the steep ravine of the Diamond River to " +
        "the east and the rugged foothills of the Grey Mountains to the " +
        "west. Far away to the northeast, you can see the wooden walls " +
        "of Sparkle, standing tall on the shores of the brilliant blue " +
        "waters of the Pen Sea. The highway continues south along an " +
        "old stone bridge that jumps over the turbulent waters of the " +
        "Copper River before entering the dark shadows of the Jade " +
        "Forest beyond.\n");

    add_trees(1);

    add_exit(THIS_DIR + "s_road1", "north");
    add_exit(THIS_DIR + "s_road2", "south");
    add_exit(THIS_DIR + "s_road2a", "southeast","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road2a", "east","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road2a", "northeast","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road2a", "southwest","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road2a", "west","@@rough@@",1,1);
    add_exit(THIS_DIR + "s_road2a", "northwest","@@rough@@",1,1);

    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Bright Road here while a matching ravine jumps down " +
        "to the Copper River to the south.\n");
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

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
banks()
{
    write("The ravine that dives steeply down towards the river looks too " +
        "dangerous for you to climb down!\n\n" +
        "You are unable to go in that direction!\n");
    return 1;
}
/* banks */

/*
 * Function name:        rough
 * Description  :        Gives an explanation for why the mortal cannot travel
                         in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
rough()
{
    write("The foothills are far too treacherous and difficult to climb here, " +
        "it looks like you will have to follow the Bright Road instead.\n");
    return 1;
}
/* rough */