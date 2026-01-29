/*      n_road2a.c                       Styles.   3 Mar 1993
 *
 *  This is a hastily constructed room meant to extend certain roads
 *  and make Style's map consistent with the actual room layouts.
 *  (Gorboth, May 2010)
 *
 *  Added fishing properties allowing fishing from bridge - Arman 2021
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

public void drink_message(string from);

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
    set_long("You are walking along the Dark Road, somewhere north of the " +
        "crossroads near the city of Sparkle. A rugged mountain spur " +
        "divides the grassy fields west of the road, while the gentle banks " +
        "of the Diamond River follow the east side of the road. Beyond " +
        "the river, soggy moorlands stretch out for miles towards the blue " +
        "waters of the Pen Sea which dominates the eastern horizon, while " +
        "the jagged peaks of the Grey Mountains seem to circle the rest of " +
        "the valley in every other directions. Following this road will " +
        "take you north towards the ancient dwarven homeland of Dwarfheim " +
        "and south towards the legendary city of Sparkle.\n");

    add_trees(1);

    add_exit(THIS_DIR + "moor_path","north");
    add_exit(THIS_DIR + "n_road2","south");

    set_no_exit_msg(({"northeast","southeast","east"}),
        "The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you find a bridge?\n");
    set_no_exit_msg(({"southwest","west","northwest"}),
        "In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");

    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just west " +
        "of the road, making passage in that direction impossible.\n");
    add_item(({"river","diamond river"}),
        "The Diamond River twists lazily across the plains and moors " +
        "of the valley just east of the road here. There appear to " +
        "be a couple of bridges if you wanted to cross to the " +
        "other side.\n");
    add_item(({"bridges","bridge"}),
        "You can see two bridges here, one to the north and one to the " +
        "south. Both look like they could take you to the moors on the " +
        "other side of the river.\n");
    add_item(({"north bridges","north bridge","stone bridge",
            "old stone bridge"}),
        "There is an old stone bridge which crosses the river into the " +
        "moorlands not far north of you.\n");
    add_item(({"south bridges","south bridge","wooden bridge","wood bridge",
            "old wood bridge","old wooden bridge"}),
        "This is an old wooden bridge, not in the best repair, but it " +
        "should give you a path across the river to the moorlands " +
        "on the other side.\n");
    add_item(({"moor", "moors", "moorland"}),
        "The gentle green foothills of the Grey Mountains turn into " +
        "soggy moorland as they flatten out to the east. There are " +
        "two bridges you can see that can take you across the river " +
        "to the heart of the moorlands.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
        "Somewhere over the moors, off to the southeast, lies Sparkle," +
        "the legendary port city which is the hub of the " +
        "Pen Sea. The town appears to be quite lively, as if it " +
        "never sleeps, a feeling which is only accented by the fact " +
        "that there appears to be an endless stream of ships which " +
        "are either arriving or departing from the great port.\n");

    set_drink_from(({"stream", "river", "diamond river"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(LIVE_I_CAN_FISH, "freshwater");
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
    init_drink();
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */
