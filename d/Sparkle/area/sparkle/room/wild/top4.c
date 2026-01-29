/* 	top4.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("High plateau");
    set_long("\n"+
        "In a canyon.\n"+
        "The canyon is narrower here but you should be able to pass anyway.\n"+
        "");

    add_exit ("top3","north");
    add_exit ("top5","west");

    add_item(({"canyon" }),
        "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

