/* 	
 * field6.c			Styles.   3 Mar 1993
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
    set_items_driver();
    set_herbs();

    set_short("A large grassy field");
    set_long("You are walking along a small trail that follows the northern " +
        "bank of the Diamond River as it wanders east towards the Pen Sea. " +
        "The land all around you is filled with wide fields of tall " +
        "yellow and green grass, haphazardly decorated with splashes of " +
        "colour from dozens of beautiful wildflowers which grow around the " +
        "small groves of trees that dot the plains. The jagged peaks " +
        "of the Grey Mountains rise up high above you to the north " +
        "and west, framing the perimeter of Sparkle valley. To the " +
        "north, you can see a tumbled heap of stone jutting out of " +
        "the fields, appearing to be the ruined remnants of some ancient " +
        "building. The trail you are walking on connects back to the " +
        "Dark Road to the east and continues to follow the river " +
        "to the northwest.\n");

    add_trees(0);

    add_exit(THIS_DIR + "ruin","north",0,1,1);
    add_exit(THIS_DIR + "field7","northeast",0,1,1);
    add_exit(THIS_DIR + "bridge_n","east");
    add_exit(THIS_DIR + "field6", "southeast", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "field6", "south", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "field6", "southwest", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "field6", "west", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "pond", "northwest");

    add_item(({"river","diamond river"}),
        "This appears to be the Diamond River, cutting through the fields " +
        "as it winds its way south towards Sparkle before emptying out into " +
        "the Pen Sea.\n");
    add_item(({"bridge","stone bridge"}),
        "You can see a stone bridge crossing the river just east of " +
        "here.\n");
    add_item(({"heap","tumbled heap","ruin","ruins","building",
                "ancient building"}),
        "It is hard to say for sure, but it seems like this mound is the " +
        "ruins of some ancient building. Although, who would build " +
        "something out in the middle of these plains is a mystery to you.\n");
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