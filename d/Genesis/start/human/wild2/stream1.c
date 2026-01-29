/* 	stream1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("By the stream");
    set_long("\n"+
             "Down by the stream.\n"+
             "Across the stream you see the stockade of Sparkle. A sewer pipe\n"+
             "from somewhere inside the village sends a stream of sewage into the\n"+
             "flowing water. The stream is a little less beautiful downstream...\n"+
             "");

    add_exit(THIS_DIR + "stream2","west");
    add_exit(THIS_DIR + "outlet","east");

    add_item(({"stream","sewage" }),
             "");
    add_item(({"stockade" }),
             "The stockade is as high and sturdy as ever.\n"+
             "");
    add_item(({"village","sparkle","Sparkle" }),
             "A magnificent village even though the sewage smells less than pleasant.\n"+
             "");
    add_item(({"sewer pipe","pipe" }),
             "The pipe is about a decimetre in diameter. The sewage doesn't\n"+
             "smell very good at all. In fact, you feel a bit nauseous.\n"+
             "");
    add_item(({"water" }),
             "It is rather polluted by the sewage.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_cmd_item( ({ "from stream", "from pipe", "water" }),
                  "drink", "@@drink" );

}

string
drink() {
    return "Yuk! This water was foul. You get a bad taste in your mouth.\n";
}
