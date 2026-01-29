/*
 *  IGARD_DEEP_PRISON + "entry_stair6.c"
 *
 *  Stairwell down into the prisons below Isengard.
 *
 *  Last modified by Alto, 10 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "prison_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "Looking up the stairwell, you see the steps vaulting away "
    + "into shadow. Below, the tight stairwell twists and turns on its "
    + "descent into the depths of Isengard.\n";
}


public void
create_gondor()
{
    set_short("A narrow twisting stairwell");
    set_long(stairwell_long_desc() + long_extratext());

    prison_add_items();
    stairwell_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage"}), 
        stairwell_long_desc() + long_extratext());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "entry_stair5",        "southwest");
    add_exit(IGARD_DEEP_PRISON + "entry_stair7",        "down");

    reset_room();
}
