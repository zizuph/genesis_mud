/* 
 *	bridge_n.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

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
    set_items_driver();
    set_herbs();

    set_short("North end of bridge");
    set_long("You are standing on the north side of a wide stone bridge " +
        "which spans the Diamond River as it rushes by. The Grey Mountains " +
        "rise up to touch the sky as they dominate the northern and " +
        "western horizon with jagged peaks of stone. You are mostly " +
        "surrounded by grassy plains which melt into misty moors as " +
        "the land approaches the sparkling blue waters of the Pen Sea " +
        "that stretches across the eastern horizon. The highway known as " +
        "the Dark Road continues to run north and south here, connecting " +
        "Sparkle with the lands to the north. There appears to be an " +
        "old trail which wanders off the road, following the river to " +
        "the west.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field7","north");
    add_exit(THIS_DIR + "field6","west");
    add_exit(THIS_DIR + "bridge_s","south");
    add_exit(THIS_DIR + "bridge_n", "northeast", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "bridge_n", "southeast", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "bridge_n", "east", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "ruin", "northwest",0,1,1);
    add_exit(THIS_DIR + "bridge_n", "southwest", "@@riv@@",1,1);

    add_item(({"bridge","wide bridge","stone bridge","wide stone bridge",
            "ancient stone bridge","ancient bridge"}),
        "Ancient and weathered, yet still strong and sturdy, this " +
        "bridge climbs over the rushing waters of the Diamond River " +
        "below. However, the longer you stand here looking at the " +
        "bridge, the more it gives you a slightly uneasy feeling.\n");
    add_item(({"moor", "moors", "moorland"}),
        "The gentle green foothills of the Grey Mountains turn into " +
        "a misty moorland as they flatten out to the east. There are " +
        "two bridges you can see that can take you across the river " +
        "to the heart of the moorlands.\n");
    add_item(({"mist","mists"}),
        "Dense mists swirl and settle across the vast moorlands that "  +
        "stretch out to the east.\n");
    add_item(({"trail","old trail","dirt trail","old dirt trail"}),
        "This is an old dirt trail that just seems to wander westward along " +
        "the banks of the river.\n");

    set_drink_from(({"stream", "river", "diamond river"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
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
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the river in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
riv()
{
    write("The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you use the bridge to the north?\n");
    return 1;
}
/* riv */

/*
 * Function name:        moor
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the moors in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
moor()
{
    write("Dense mists swirl across the wet moors that begin east of the " +
        "Dark Road. There does not appear to be a safe way to enter the " +
        "moors in this direction.\n");
    return 1;
}
/* moor */