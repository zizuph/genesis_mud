/* 	forest1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Green forest");
    set_long("\n"+
             "You are standing in a luscious green forest listening to the\n"+
             "many birds in the air. A sense of ease and tranquillity rests\n"+
             "over this place. Between the trees to the far west, you\n"+
             "can see the mountains.\n"+
             "");

    add_exit("slope","west");
    add_exit("orc_road3","south");

    add_item(({"mountains","trees","forest" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

