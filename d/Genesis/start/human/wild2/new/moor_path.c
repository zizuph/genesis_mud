/*      moor_path.c                       
 *
 *  This is a hastily constructed room meant to extend certain roads
 *  and make Style's map consistent with the actual room layouts.
 *  (Gorboth, May 2010)
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();
    set_items_driver();
    set_herbs();

    set_short("Dark road");
    set_long("You are walking along the Dark Road, somewhere north of the " +
        "crossroads near the city of Sparkle. A rugged mountain spur " +
        "divides the grassy fields west of the road, while the gentle banks " +
        "of the Diamond River follow the east side of the road. An old " +
        "stone bridge stands just east of you here, crossing the river " +
        "and leading into the soggy moorlands which stretch out for miles. " +
        "Stretching up to pierce the sky, the jagged stone peaks of the " +
        "Grey Mountains huddle around the perimeter of the rest of the " +
        "valley. The highway runs in a straight line, taking you north " +
        "towards the ancient dwarven homeland of Dwarfheim or south towards " +
        "the legendary city of Sparkle.\n");

    add_trees(1);

    add_exit(THIS_DIR + "bridge_s","north");
    add_exit(THIS_DIR + "moor_bridge", "east");
    add_exit(THIS_DIR + "n_road2a","south");
    add_exit(THIS_DIR + "moor_path", "northeast", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "moor_path", "southeast", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "moor_path", "west", "@@spur@@", 1,1);
    add_exit(THIS_DIR + "moor_path", "northwest", "@@spur@@", 1,1);
    add_exit(THIS_DIR + "moor_path", "southwest", "@@spur@@",1,1);

    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just west " +
        "of the road, making passage in that direction impossible.\n");
    add_item(({"old bridge","bridge","old stone bridge","stone bridge"}),
        "This is an old stone bridge, yet still in good repair, that " +
        "will lead you across the rushing waters of the Diamond River " +
        "and into the wet moorlands on the other side.\n");
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

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "river", "diamond river"}));
}

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

/*
 * Function name:        riv
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the river in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
riv()
{
    write("The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you use the bridge to the east?\n");
    return 1;
}
/* riv */

/*
 * Function name:        spur
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
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