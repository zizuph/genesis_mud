/* 	n_road1.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Dark road");
    set_long("\n"+
        "You're walking along a dark road. Far to the north are \n"+
        "the mountains and south is a crossroad.\n"+
        "");

    add_exit ("n_road2","north");
    add_exit ("crossroad","south");

    add_item(({"mountains","crossroad" }), "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

}

