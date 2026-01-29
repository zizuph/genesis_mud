/*
 * 	bridge_s.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 *
 *  Added fishing properties allowing fishing - Arman 2021
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();
    set_items_driver();
    set_herbs();

    set_short("South end of bridge");
    set_long("You are standing on the south side of a wide stone bridge " +
        "which climbs across the rushing blue water of the Diamond " +
        "River. Grassy fields climb over the gentle foothills that " +
        "fall down from the jagged heights of the Grey Mountains that " +
        "dominate the western horizon. The tip of a rugged spur of " +
        "mountains which has pierced into the heart of the valley, is " +
        "visible to the southwest, while the fields slowly turn into " +
        "vast moorlands on the eastern side of the river which reach " +
        "for miles before they reach the coast of the Pen Sea. The " +
        "Dark Road runs north and south here, connecting Sparkle with " +
        "the lands to the north. You notice a small dirt path that " +
        "follows the river west from here.\n");

    add_trees(0);

    add_exit(THIS_DIR + "bridge_n","north");
    add_exit(THIS_DIR + "field1","west");
    add_exit(THIS_DIR + "moor_path","south");

    set_no_exit_msg(({"northeast","northwest","east","southeast"}),
        "The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you use the bridge to the north?\n");
    set_no_exit_msg(({"southwest"}),
        "The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");

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
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley to the " +
        "southwest, making passage in that direction impossible.\n");
    add_item(({"mist","mists"}),
        "Dense mists swirl and settle across the vast moorlands that "  +
        "stretch out to the east.\n");
    add_item(({"path","small path","dirt path","small dirt path"}),
        "This is a small dirt path which follows the river west towards " +
        "the mountains.\n");

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