/*
 * 	moor1.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_moor();
    set_herbs();

    set_short("Misty moor");
    set_long("You find yourself on a stone path in the middle of some " +
        "mist covered moors just north of Sparkle. Low hills, blanketed " +
        "with fields of tall green grasses and vividly coloured flowers, " +
        "rise and fall into the mist. A small stream twists around " +
        "the hills and the occasional grove of trees, running merrily " +
        "off to the south. A misty fog rises from the wetlands that " +
        "surround you, covering everything in sight and preventing you from " +
        "seeing too far ahead. You suspect it would be a smart idea to stay " +
        "on the path itself, which runs west towards the Dark " +
        "Road and east towards the Pen Sea, with a small branch that " +
        "follows the stream to the south.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor_bridge","west");
    add_exit(THIS_DIR + "stream3","south");
    add_exit(THIS_DIR + "moor2","east");
    add_exit(THIS_DIR + "moor1","southeast","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor1","northeast","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor1","southwest","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor1","northwest","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor1","north","@@moor@@",1,1);

    add_item(({"stream","small stream"}),
        "There is a small stream that flows across the moors to the south, " +
        "winding its way along the edge of the stone path.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "water"}));
}

void

init()
{
    ::init();
    init_drink();
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description of drinking from the stream
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
 * Function name:        moor
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the moors in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
moor()
{
    write("You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");
    return 1;
}
/* moor */