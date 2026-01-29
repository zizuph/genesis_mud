/* 	
 * field9.c			Styles.   3 Mar 1993
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
    set_items_field();
    set_items_darkroad();
    set_herbs();

    set_short("Dark Road");
    set_long("You are following the Dark Road as it travels east and north " +
        "on the northern edge of Sparkle valley. The dark and treacherous " +
        "pass known as Renegade Cut slices through the Grey Mountains to " +
        "the north. The jagged slopes of the mountains become almost sheer " +
        "as they rise straight up along the sides of the pass, offering " +
        "no escape for any unwary traveller who might wander into an " +
        "ambush. To the west, a small stream of water empties out from " +
        "a small waterfall that crashes down the rocky slopes. Spread " +
        "out to the south are miles of grassy fields, dotted with " +
        "dozens of colourful wildflowers. A small dirt path wanders " +
        "through the fields, following the stream.\n");

    add_trees(0);

    add_exit(THIS_DIR + "pass","north");
    add_exit(THIS_DIR + "wfall","west");
    add_exit(THIS_DIR + "pond","south");
    add_exit(THIS_DIR + "field10","east");
    add_exit(THIS_DIR + "field9","northeast","@@mount@@", 1,1);
    add_exit(THIS_DIR + "field9","northwest","@@mount@@", 1,1);
    add_exit(THIS_DIR + "field9","southwest","@@riv@@", 1,1);
    add_exit(THIS_DIR + "ruin","southeast",0,1,1);

    add_item(({"pass","mountain pass","cut","renegade cut"}),
	    "This is the mountain pass known as Renegade Cut. Travel through " +
        "the cut is now seen as nothing more than suicide as bandits now " +
        "control the mountain pass and this highway has since been given " +
        "its name of the Dark Road.\n");
    add_item(({"waterfall","stream","water","small stream","small waterfall", 
            "mountainside","river","diamond river"}),
	    "Crashing down the rocky mountainside just west of the road here " +
        "is a small waterfall, with a stream of water trailing away " +
        "to begin its journey towards the Pen Sea as the Diamond " +
        "River.\n");
    add_item(({"path","small path","dirt path","small dirt path"}),
        "A small dirt path breaks away from the Dark Road here, following " +
        "the small stream that flows across the fields to the south.\n");
    
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
        "the stream. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the stream.\n");
}
/* drink_message */

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
mount()
{
    write("In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");
    return 1;
}
/* mount */

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