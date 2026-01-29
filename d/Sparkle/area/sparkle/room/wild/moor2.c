/* 	moor2.c			Styles.   3 Mar 1993
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
             "You are walking the gentle hills of a misty moor.\n"+
             "Looking north you see the mountain ridge, east you see the sea, west you\n"+
             "spot higher grounds and far south you see the village of Sparkle.\n"+
             "");

    add_exit("moor1","west");
    add_exit("stockade","south");
    add_exit("moor3","east");

    add_item(({"moor","hills","sea","ridge","mountain","mountains" }),
             "");
    add_item(({"sparkle","Sparkle","village" }),
             "Sparkle is a small human village by the shore of Pensea.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

