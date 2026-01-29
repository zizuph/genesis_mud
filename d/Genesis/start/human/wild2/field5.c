/*
 * 	field5.c			Styles.   3 Mar 1993
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
    set_long("You are on a small dirt path that follows the banks of the " +
        "Diamond River. The wide blue waters of the river cut through " +
        "the grassy plains of Sparkle valley as it tumbles east towards " +
        "the Pen Sea. On the far side of the river, surrounded by tall " +
        "grasses and colourful wildflowers, you can see the broken " +
        "ruins of what was once a small cottage. With tall jagged " +
        "peaks piercing the blue sky above, the Grey Mountains huddle " +
        "around the perimeter of the valley, dominating the horizon " +
        "in almost every direction. The path continues along the " +
        "riverbanks to the west and moves deeper into the fields " +
        "to the south.\n");

    add_trees(1);

    add_exit(THIS_DIR + "field4", "west");
    add_exit(THIS_DIR + "field2", "south");
    add_exit(THIS_DIR + "field3", "southwest",0,1,1);

    set_no_exit_msg(({"east","southeast","northwest","north","northeast"}),
        "The stream is too wide to cross here, you will have to find a " +
        "bridge or something.\n");

    add_item(({"path","dirt path","small dirt path","small path",
            "narrow path","narrow dirt path","branch"}),
        "This small dirt path follows along the banks of the Diamond " +
        "River to the west and trails away into the fields to the " +
        "south.");
    add_item(({"mountain spur","spur","mountainside"}),
        "The rugged mountainside which juts up into the sky before you, " +
        "is the eastern end of a mountain spur that has cut through the " +
        "middle of Sparkle valley.");
    add_item(({"mountains","mountain","grey mountains"}),
        "They Grey Mountains surround the entire Sparkle valley, including " +
        "the jagged spur that juts up immediately before you to the south.");
    add_item(({"stream","river","diamond river","water","waters"}),
        "The rushing waters of the Diamond River rush eastward on a journey " +
        "to the Pen Sea.\n");
    add_item(({"bank","riverbank","riverbanks","banks"}),
        "The banks of the river are filled with tall grass and " +
        "colourful wildflowers.\n");
    add_item(({"cottage","building","mound","ruins","wall","walls",
            "chimney","broken ruins","ruin","stone wall","stone walls",
            "stone chimney","stone cottage","stone building","broken stone",
            "broken stones","broken stone walls","broken stone wall",
            "old cottage","old stone cottage"}),
        "On the far side of the river, to the northeast, you can see the " +
        "ruins of an old stone cottage. All that is left now are broken " +
        "stone walls clustered around a tall chimney that rises high " +
        "above the fields. There is no way to reach the cottage from here, " +
        "you will have to find a bridge to cross the river.\n");

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
 * Description  :        Provides a description for drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */