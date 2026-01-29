/*
 * 	n_shore.c			Styles.   3 Mar 1993
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

    set_short("North shore");
    set_long("You are currently walking along a narrow path of fieldstones " +
        "that follows a small stream to the west and enters a heavy fog " +
        "to the north. On the other side of the stream, a tall wooden " +
        "stockade rises up, the city of Sparkle resting safely behind. " +
        "To the east, the heavy waves of the Pen Sea roll heavily " +
        "into a long sandy beach that extends out onto a peninsula to " +
        "the northeast. The occasional grove of trees peeks out from " +
        "behind mists that cover the low grassy hills of the moors " +
        "that stretch across the northern horizon.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor3","north");
    add_exit(THIS_DIR + "stockade","west");
    add_exit(THIS_DIR + "moor4","northeast",0,1,1);
    add_exit(THIS_DIR + "moor2","northwest",0,1,1);

    set_no_exit_msg(({"southeast","east"}),
        "You take a step into the rolling waves of the Pen Sea that " +
        "are crashing up against the shore. It seems obvious that you " +
        "cannot go any further in this direction.\n");
    set_no_exit_msg(({"southwest","south"}),
        "You don't think you could swim across the stream, especially " +
        "since there is a tall wooden wall on the other side!\n");

    add_item(({"stream","small stream" }),
        "This small stream empties into the Pen Sea here, " +
        "bordered a stone path on one side and a wooden stockade " +
        "on the other.\n");
    add_item(({"stockade","walls","wooden walls","wooden stockade","wood",
            "city walls","city wall","wall","wooden wall","tall wall",
            "sparkle","city","town","village"}),
        "The stockade is a sturdy wooden wall that surrounds the " +
        "legendary city of Sparkle. It is rather tall, and the wooden " +
        "posts are sharpened into stakes, discouraging anyone from " +
        "trying to climb over. The stockade extends east, jutting " +
        "out directly into the Pen Sea.\n");
    add_item(({"stake","post","stakes","posts","wooden post","wooden posts",
            "wooden stake","wooden stakes"}),
        "These tall wooden posts are very sharp at the top, all lashed " +
        "together to form a wall, discouraging anyone who might attempt " +
        "to climb over.\n");
    add_item(({"peninsula","beach","sandy beach","sand"}),
        "A long sandy beach has been created where the Pen Sea brushes " +
        "up against the moors here. The beach stretches out from the " +
        "walls of Sparkle just visible to the south and around a " +
        "peninsula that extends to the east before trailing off in the " +
        "distance to the north.\n");
    add_item(({"sea","coast","shore","pen sea","water","waters","waves",
            "wave"}),
        "You can see the choppy waves of the Pen Sea rolling up a sandy " +
        "beach to the southeast\n.");
    add_item(({"east horizon","eastern horizon","east"}),
        "Endless lines of massive blue waves roll across the Pen Sea as " +
        "you gaze out upon the eastern horizon.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "Endless lines of massive blue waves roll across the Pen Sea as " +
        "you gaze out upon the eastern horizon.\n");
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