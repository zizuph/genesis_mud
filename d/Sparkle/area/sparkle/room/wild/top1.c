/* 	top1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Top of trail");
    set_long("\n"+
             "Top of a steep trail.\n"+
             "The air is cooler up here in the mountains then down in the valley below.\n"+
             "A steep trail is leading down between the rocks to the east. This seems\n"+
             "to be the northern part of a mountain canyon that runs southwards from here.\n"+
             "");

    add_exit ("top2","south");
    add_exit ("gravel","east");

    add_item(({"trail","canyon","mountains","rocks" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

