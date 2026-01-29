/*
 * 	field1.c			Styles.   3 Mar 1993
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

    set_short("A large field");
    set_long("You are walking along a narrow dirt path that cuts through " +
        "a large grassy field filled with dozens of different wildflowers. " +
        "Looking to the north, you see the rushing waters of the Diamond " +
        "River slice east through the valley on its journey to empty " +
        "out into the Pen Sea. To the south, the land jumps up quickly " +
        "along a rugged mountain spur that has jabbed into the heart " +
        "of the valley. The mountains continue to wrap around the valley " +
        "along the western and northern horizon, their jagged peaks " +
        "piercing the sky itself. The path continues to dive deeper into " +
        "the fields that extend to the west, and also back east to the " +
        "Dark Road.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field2","west");
    add_exit(THIS_DIR + "bridge_s","east");
    add_exit(THIS_DIR + "field5", "northwest",0,1,1);

    set_no_exit_msg(({"north","northeast"}),
        "The stream is too wide to cross here, you will have to find a " +
        "bridge or something.\n");
    set_no_exit_msg(({"southwest","south","southeast"}),
        "The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");

    add_item(({"mountain spur","spur","mountainside"}),
        "The rugged mountainside which juts up into the sky before you, " +
        "is the eastern end of a mountain spur that has cut through the " +
        "middle of Sparkle valley.");
    add_item(({"mountains","mountain","grey mountains"}),
        "They Grey Mountains surround the entire Sparkle valley, including " +
        "the jagged spur that juts up immediately before you to the south.");
    add_item(({"south horizon","southern horizon","southwest horizon",
            "southwestern horizon","south","southwest"}),
        "You cannot really see much to the south except a massive " +
        "spur of the Grey Mountains.\n");
    add_item(({"stream","river","diamond river","water","waters"}),
        "The rushing waters of the Diamond River rush eastward on a journey " +
        "to the Pen Sea. Just east of here, you can see a stone bridge " +
        "that crosses the river.\n");
    add_item(({"bridge","wide bridge","stone bridge","wide stone bridge"}),
        "This bridge is a part of the Dark Road, crossing the Diamond " +
        "River on the way up to Dwarfheim and Larton.\n");
    add_item(({"path","dirt path","small dirt path","small path",
            "narrow path","narrow dirt path"}),
        "This small dirt path winds through the fields between the Diamond " +
        "River and the spur of the Grey Mountains that has thrust into " +
        "the valley nearby. The path goes deeper into the fields to the " +
        "west and to the Dark Road in the east.");
    add_item(({"road","dark road","highway"}),
        "Just east of these fields, the Dark Road runs north across a " +
        "wide stone bridge towards Dwarfheim and south towards the " +
        "city of Sparkle.");

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
 * Description  :        Provides a drinking message from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */