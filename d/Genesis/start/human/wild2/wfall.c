/* 	
 * wfall.c			Styles.   3 Mar 1993
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
    set_items_field();
    set_items_driver();
    set_herbs();

    set_short("By a waterfall");
    set_long("Crashing down from the rugged mountainside, the rushing " +
        "waters of a cool mountain stream transform into a majestic " +
        "waterfall. Fine drops of water spray against your face as " +
        "the stream falls into a shallow pool before winding away to " +
        "the southeast. High above you, the jagged peaks of the Grey " +
        "Mountains pierce the white clouds in the blue sky. Broad " +
        "fields cover the floor of this valley, littered with hundreds " +
        "of colourful wildflowers that peek out from behind the tall " +
        "grass and groves of trees. To the east, there appears to be a " +
        "highway leading north towards a high pass that cuts through the " +
        "mountains.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field9","east");
    add_exit(THIS_DIR + "pond","southeast",0,1,1);

    set_no_exit_msg(({"north","northeast","northwest","west"}),
        "The mountainside is far too difficult for you to climb! Perhaps " +
        "you could try using the mountain pass instead?\n");
    set_no_exit_msg(({"southwest","south"}),
        "It is impossible to cross the stream here, you will have to find " +
        "another way across.\n");

    add_item(({"spray","mist","water spray"}),
             "The spray from the water looks like a fine mist dancing " +
             "above the stream, gently caressing your face with its " +
             "gentle kiss.\n");
    add_item(({"pool","shallow pool"}),
             "This pool has gathered beneath the waterfall, collecting " +
             "the water before it pushes southeast across the valley.\n");
    add_item(({"waterfall","falls","fall","waterfalls"}),
             "This waterfall crashes down the mountainside in majestic " +
             "fashion, creating a rather idyllic setting for someone to " +
             "take a nice rest.\n");
     add_item(({"pass","mountain pass"}),
             "It is hard to see much from here, but there appears to be " +
             "a high pass through the mountains just east of here.\n"); 
     add_item(({"road","dark road","highway"}),
             "You see the Dark Road just east of here, travelling north " +
             "towards a high pass through the Grey Mountains.\n");
    add_item(({"mountainsides","mountainside"}),
             "The mountainside here is rather steep and rugged, broken " +
             "only by the beautiful waterfall which crashes down nearby.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(LIVE_I_CAN_FISH, "freshwater");
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "river", "diamond river", "falls",
        "waterfall", "waterfalls"}));
    
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
    write("Stepping closer to the waterfall, you take a refreshing drink " +
        "of water from the mountain stream.\n");
    say(QCTNAME(TP) + " takes a refreshing drink of water from the " +
        "mountain stream.\n");
}
/* drink_message */