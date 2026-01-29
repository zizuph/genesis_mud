/* 	
 * n_road1.c			Styles.   3 Mar 1993
  *
 * Updated by Varian, March 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

int do_climb(string str);

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();
    set_herbs();

    set_short("Dark road");
    set_long("You are walking along the Dark Road, just north of the " +
        "crossroads near the city of Sparkle which is barely visible to " +
        "the southeast. The highway also continues north towards the " +
        "dwarven homeland of Dwarfheim. A rugged mountain spur divides the " +
        "grassy fields west of the road, while the steep banks of the " +
        "Diamond River fall down in a ravine to the east. The jagged peaks " +
        "of the Grey Mountains seem to circle the valley in all directions, " +
        "save in the east where the blue waters of the Pen Sea shine on the " +
        "horizon.\n");

    add_trees(0);

    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Dark Road here.\n");
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just west " +
        "of the road, making passage in that direction impossible.\n");
    add_item(({"river","diamond river"}),
        "At the bottom of a steep ravine east of the road, you can see " +
        "the rushing waters of the Diamond River.\n");

    add_exit(THIS_DIR + "n_road2","north");
    add_exit(THIS_DIR + "crossroad","south");
    add_exit(THIS_DIR + "n_road1", "east", "@@banks@@", 1,1);
    add_exit(THIS_DIR + "n_road1", "northeast", "@@banks@@", 1,1);
    add_exit(THIS_DIR + "n_road1", "southeast", "@@banks@@", 1,1);
    add_exit(THIS_DIR + "n_road1", "west", "@@spur@@", 1,1);
    add_exit(THIS_DIR + "n_road1", "northwest", "@@spur@@", 1,1);
    add_exit(THIS_DIR + "orc_road1", "southwest",0,1,1);

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

}

/*
 * Function name:        init
 * Description  :        Sets up commands for the player
 */
void
init()
{
    ::init();
    add_action("do_climb","climb");
}
/* init */

/*
 * Function name:        do_climb
 * Description  :        Allows the player to attempt to climb the slope
 * Returns      :        int 1 - Explains they cannot climb
 *                       int 0 - Prompts for syntax
 */
public int
do_climb(string str)
{
    if(!strlen(str))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        "[down] [the] 'ravine' / 'slope'") &&
        str != "down")
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    write("You try to find a way to climb down the ravine, but the " +
        "steep slope makes it too dangerous from here.\n");
    SAYBB(" looks for a way down the ravine, but cannot seem to " +
        "find one.");
    return 1;
}
/* do_climb */

/*
 * Function name:        banks
 * Description  :        Gives an explanation for why the mortal cannot climb
                         down the ravine
 * Returns      :        int 1 - denies moving along the exit path
 */
int
banks()
{
    write("The ravine that dives steeply down towards the river looks too " +
        "dangerous for you to climb down!\n\n " +
        "You are unable to go in that direction!\n");
    return 1;
}
/* banks */

/*
 * Function name:        spur
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
spur()
{
    write("In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");
    return 1;
}
/* spur */
