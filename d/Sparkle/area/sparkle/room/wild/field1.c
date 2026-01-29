/* 	field1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("A large field");
    set_long("\n"+
             "A large field extends far in a north-west direction.\n"+
             "With a stream to your north and the mountains to the south, you are left\n"+
             "with the options of going either east towards the bridge or west out on\n"+
             "the field.\n"+
             "");

    add_exit("field2","west");
    add_exit("bridge_s","east");

    add_item(({"mountains" }),
             "");
    add_item(({"field" }),
             "It's quite large.\n"+
             "");
    add_item(({"stream" }),
             "Nah, it's too wide to jump.\n"+
             "");
    add_item(({"bridge" }),
             "It's not that far away. Just a little to the east.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

