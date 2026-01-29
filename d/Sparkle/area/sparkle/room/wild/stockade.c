/* 	stockade.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("By the stockade");
    set_long("\n"+
        "You are standing by the stockade, north of the village of Sparkle.\n"+
        "The woodwork is strong and well built so you might as well forget any\n"+
        "thoughts of breaching it. To the north is a large and misty moor.\n"+
        "");

    add_exit ("moor2","north");
    add_exit ("stream3","west");
    add_exit ("n_shore","east");

    add_item(({"moor","mist" }),
        "");
    add_item(({"stockade","walls" }),
        "The stockade runs all around Sparkle and is part of\n"+
        "the villages defense. It looks very sturdy.\n"+
        "");
    add_item(({"sparkle","Sparkle","village" }),
        "Sparkle is a small human village by the shore of Pensea.\n"+
        "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

