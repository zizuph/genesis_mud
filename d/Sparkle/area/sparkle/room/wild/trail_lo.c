/* 	trail_lo.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Lower part of a trail");
    set_long("\n"+
             "You stand at the bottom of a long trail.\n"+
             "The trail goes west up the mountainside at a steep angle. It also bends\n"+
             "to the north where it enters a low valley. Up at the top of the trail you\n"+
             "think you can see a fog of some kind.\n"+
             "");

    add_exit ("grove","north");
    add_exit ("trail_hi","west");

    add_item(({"mountainside","trail","valley" }),
             "");
    add_item(({"fog" }),
             "Its more like a gray mist that covers the area up there.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

