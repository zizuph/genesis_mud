/* 	moor1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Misty moor");
    set_long("\n"+
             "You are walking on a misty moor slanting down towards the sea.\n"+
             "The ground is unsafe to the north as it suddenly opens up into a steep\n"+
             "crevice. Going east will take you closer to the mountain but also\n"+
             "further out on the moor.\n"+
             "");

    add_exit("bridge_n","west");
    add_exit("stream3","south");
    add_exit("moor2","east");

    add_item(({"moor","sea","ground","crevice","mountain" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

