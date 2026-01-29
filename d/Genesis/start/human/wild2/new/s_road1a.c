/*
 *  /d/Genesis/start/human/wild2/s_road1a.c
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
    set_long("You are walking along the Bright Road, a long straight " +
        "highway of large white stones that runs south from Sparkle, " +
        "through fields full of tall grass and colourful wildflowers, past " +
        "the Jade Forest and into the wilderness beyond. A steep ravine " +
        "breaks away from the road to the east where the Diamond River " +
        "rushes past, while the west side of the road is filled with the " +
        "rugged foothills of the Grey Mountains that tower high above " +
        "you. In the distance to the south, you can see the Bright Road " +
        "cutting a path of white through the dark shadows of the Jade " +
        "Forest, while a busy crossroads with the Orc Road and the Dark " +
        "Road can be found just north of here, not far from the wooden " +
        "walls of Sparkle which sit upon the Pen Sea.\n");

    add_trees(1);

    add_exit(THIS_DIR + "crossroad", "north");
    add_exit(THIS_DIR + "s_road1", "south");
    add_exit(THIS_DIR + "s_road1a", "southeast","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road1a", "east","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road1a", "northeast","@@banks@@",1,1);
    add_exit(THIS_DIR + "s_road1a", "southwest","@@rough@@",1,1);
    add_exit(THIS_DIR + "s_road1a", "west","@@rough@@",1,1);
    add_exit(THIS_DIR + "s_road1a", "northwest","@@rough@@",1,1);

    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Bright Road here.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Immediately east of you here, the horizon is dominated by the " +
        "wooden stockade surrounding the city of Sparkle, and the blue " +
        "waters of the Pen Sea that spreads across the horizon beyond.\n");
    add_item(({"sparkle","city","town","village","port"}),
        "The city of Sparkle, widely hailed as the greatest port in the " +
        "world, lies on the other side of the Diamond River. You suspect " +
        "that you can get there by first travelling to the crossroads " +
        "that are just north of you here.\n");
    add_item(({"wall", "walls", "wood wall", "wooden walls",
            "sparkle wall", "sparkle walls","stockade","wooden stockade"}),
        "A tall wooden wall graces the eastern horizon, surrounding the " +
        "legendary city of Sparkle.\n");
    add_item(({"crossroad","crossroads"}),
        "Just north of you, there are four great highways which intersect " +
        "in a large and busy crossroads.\n");
    add_item(({"hill","foothill","foothills","hills","rugged foothills",
            "rugged hills","rugged foothill","rugged hill"}),
        "Broken land rises up before you to the west as rugged " +
        "foothills transform into the jagged and rocky peaks of the " +
        "Grey Mountains.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        banks
 * Description  :        Gives an explanation for why the mortal cannot travel
                         down the ravine
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
    write("The foothills are far too treacherous and difficult to climb " +
        "here, it looks like you will have to follow the Bright Road " +
        "instead.\n");
    return 1;
}
/* rough */