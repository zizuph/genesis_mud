/*
 * 	field8.c			Styles.   3 Mar 1993
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
    set_items_driver();
    set_items_field();
    set_herbs();
    
    set_short("A large field");
    set_long("You are walking along a small dirt path following the " +
        "banks of a wide stream that cuts through the fields to the east. " +
        "The river crashes down the mountainside in the form of a " +
        "majestic waterfall, spraying out in a fine mist as it crashes " +
        "into the valley. The fields are filled with tall grasses and " +
        "a huge variety of brightly coloured wildflowers rising up over " +
        "the rolling hills. Rising up all around you, the Grey Mountains " +
        "surround the valley, their rugged peaks carving into the " +
        "horizon. The path you are on leaves the stream to wind its " +
        "way west into the mountains, heading towards a particularily " +
        "large tree.\n");

    add_trees(1);

    add_exit(THIS_DIR + "big_tree","west");
    add_exit(THIS_DIR + "field4","south");
    add_exit(THIS_DIR + "field8", "southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "field8", "east","@@riv@@",1,1);
    add_exit(THIS_DIR + "field8", "southeast","@@riv@@",1,1);
    add_exit(THIS_DIR + "field8", "northwest","@@riv@@",1,1);
    add_exit(THIS_DIR + "field8", "north","@@riv@@",1,1);
    add_exit(THIS_DIR + "field8", "northeast","@@riv@@",1,1);

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
     add_item(({"tree","large tree","huge tree"}),
             "There are several groves of trees scattered around the " +
             "valley, but one tree to the west in particular catches " +
             "your attention, growing almost twice as high as any other " +
             "tree you can see around here!\n");
    add_item(({"path","dirt path"}),
             "This dirt path seems to follow the stream to the east, " +
             "while delving deeper into the mountains to the west.\n");
    add_item(({"river","stream","diamond river"}),
             "Crashing down from the mountains in a spectacular " +
             "waterfall, this stream begins its journey across " +
             "valley here, before it turns into the mighty Diamond " +
             "River and empties out into the Pen Sea near the famous " +
             "port of Sparkle.\n");
    add_item(({"mountainsides","mountainside"}),
             "The mountainside here is rather steep and rugged, broken " +
             "only by the beautiful waterfall which crashes down nearby.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
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
    write("The stream is too wide to cross here, you will have to find a " +
        "bridge or something.\n");
    return 1;
}
/* riv */

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");
    return 1;
}
/* mount */