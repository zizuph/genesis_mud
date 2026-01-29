/* 	stream2.c			Styles.   3 Mar 1993
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
             "Following the stream to the east will take you closer to the sea\n"+
             "while going west will leave you standing on the Bright road.\n"+
             "");

    add_exit(THIS_DIR + "s_road2","west");
    add_exit(THIS_DIR + "stream1","east");

    add_item(({"stream","sea","road" }),
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
