/*
 * 	stream3.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 *
 *  Added fishing properties allowing fishing - Arman 2021
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_moor();
    set_items_driver();
    set_herbs();

    set_short("By the stream");
    set_long("You are walking along a small path made of fieldstones that " +
        "follows the Diamond River, turning east to follow a small stream " +
        "that has branched off to empty into the Pen Sea. On the south side " +
        "of the stream you can see the tall wooden stockade that surrounds " +
        "the legendary city of Sparkle. To the north and east, a heavy " +
        "mists settles down across the low hills of the moor as if trying " +
        "to conceal the tall grasses and small groves of trees that " +
        "grow there. The path leads deeper into the moors to both the " +
        "north and the east.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor1","north");
    add_exit(THIS_DIR + "stockade","east");
    add_exit(THIS_DIR + "moor2","northeast",0,1,1);
    
    set_no_exit_msg(({"northwest","west"}),
        "The rushing waters of the Diamond River tumble past here, " +
        "preventing you from going any further in this direction.\n");
    set_no_exit_msg(({"southwest","south","southeast"}),
        "You cannot cross the stream as there is a tall wooden wall right " +
        "on the other side!\n");

    add_item(({"stream","small stream"}),
        "This small stream runs merrily east towards the Pen Sea, " +
        "bordered a stone path on one side and a wooden stockade " +
        "on the other.\n");
    add_item(({"stockade","walls","wooden walls","wooden stockade","wood",
            "city walls","city wall","wall","wooden wall","tall wall",
            "sparkle","city","town","village"}),
        "The stockade is a sturdy wooden wall that surrounds the " +
        "legendary city of Sparkle. It is rather tall, and the wooden " +
        "posts are sharpened into stakes, discouraging anyone from " +
        "trying to climb over.\n");
    add_item(({"stake","post","stakes","posts","wooden post","wooden posts",
            "wooden stake","wooden stakes"}),
        "These tall wooden posts are very sharp at the top, all lashed " +
        "together to form a wall, discouraging anyone who might attempt " +
        "to climb over.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "Looking to the northwest, you can see the jagged peaks of the Grey " +
        "Mountains enclose the valley, separating it from distant " +
        "destinations such as Dwarfheim or the city of Larton.\n");
    add_item(({"west horizon","western horizon","west"}),
        "Looking to the west, the Grey Mountains are at their most " +
        "intimidating, blocking all passage save where the Orc Road " +
        "cuts through the high pass and into the orcish homelands " +
        "beyond.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "Looking to the west, the Grey Mountains are at their most " +
        "intimidating, blocking all passage save where the Orc Road " +
        "cuts through the high pass and into the orcish homelands " +
        "beyond.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the southeast.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the south.\n");
    add_item(({"river","diamond river"}),
        "Crashing through the land just east of you, the Diamond River " +
        "tumbles south on its journey to the Pen Sea.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(LIVE_I_CAN_FISH, "freshwater");
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
 * Description  :        Gives a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}