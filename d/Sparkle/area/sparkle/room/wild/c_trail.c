/* 	c_trail.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{

    set_short("Coast trail");
    set_long("\n"+
        "A trail not far from the coast.\n"+
        "As you move along the trail you notice an odd wind blowing in from\n"+
        "the sea. The wind sweeps across the moor up towards the mountains and\n"+
        "somewhere along the way a thick mist develops to obstruct your view.\n"+
        "");

    add_exit("moor3","south");

    add_item(({"trail","sea","moor" }),
        "");
    add_item(({"mist" }),
        "Gosh! This is not a mist. It's a dense fog! Someone could approach\n"+
        "and surprise you from any direction without too much skill.\n"+
        "You better be careful not to step into a foxhole.\n"+
        "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

