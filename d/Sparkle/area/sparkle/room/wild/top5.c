/* 	top5.c			Styles.   3 Mar 1993
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
             "A narrow gorge leads north from here.\n"+
             "You are standing at the edge of a 40 feet drop.\n"+
             "The canyon continues to the south 15 feet beyond the drop where it\n"+
             "bends out of view. Climbing might be difficult and it is too far to jump.\n"+
             "");

    add_exit ("top4","east");
    add_exit ("/d/Sparkle/area/cavern/room/entrance1","north");

    add_item(({"canyon","edge","drop" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

