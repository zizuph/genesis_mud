/* 	stream3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("By the stream");
    set_long("\n"+
        "You are walking on the east side of a stream.\n"+
        "Across on the other side you see the dark road. A little to the south\n"+
        "is the stockade of Sparkle. The stream bends to cut off your access to\n"+
        "the gates as it runs too close to the walls for you to pass.\n"+
        "");

    add_exit ("moor1","north");
    add_exit ("stockade","east");

    add_item(({"stream" }),
        "The stream runs close to the stockade and is about 5 metres wide.\n"+
        "");
    add_item(({"stockade","walls" }),
        "The stockade runs all around Sparkle and is part of\n"+
        "the villages defense. It looks very sturdy.\n"+
        "");
    add_item(({"road","gates" }),
        "");
    add_item(({"sparkle","Sparkle","village" }),
        "Sparkle is a small human village by the shore of Pensea.\n"+
        "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_cmd_item( ({ "from stream", "water" }),
        "drink", "@@drink" );

}

string
drink()
{
    return "You drink a little water.\n";
}

