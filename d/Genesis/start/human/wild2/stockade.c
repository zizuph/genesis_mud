/*
 * 	stockade.c			Styles.   3 Mar 1993
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
    set_herbs();

    set_short("By the stockade");
    set_long("You are standing near a tall wooden stockade, north of the " +
        "village of Sparkle, sitting on the edge of the moors. The woodwork " +
        "is tall, strong and well built, obviously designed to prevent " +
        "anyone entering the city from this direction. A small stream " +
        "winds past, cutting between you and the city walls as it wanders " +
        "east towards the Pen Sea. A path of fieldstones rests on the " +
        "wet ground of the moors, following the stream to both the " +
        "west and east, in addition to travelling north deeper into " +
        "the dense mists that surround the low hills of the moorlands.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor2","north");
    add_exit(THIS_DIR + "stream3","west");
    add_exit(THIS_DIR + "n_shore","east");
    add_exit(THIS_DIR + "moor3","northeast",0,1,1);

    set_no_exit_msg(({"northwest"}),
        "You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");
    set_no_exit_msg(({"southwest","southeast","south"}),
        "You don't think you could swim across the stream, especially " +
        "since there is a tall wooden wall on the other side!\n");

    add_item(({"stream","small stream" }),
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
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the southeast.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the south.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the southwest.\n");

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