/*
 *  IGARD_DEEP_PRISON + "second_stair5.c"
 *
 *  Stairwell in the prisons below Isengard.
 *
 *  Last modified by Alto, 11 November 2001
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
    return "Looking down, you see the beginning of a dark damp corridor. "
    + "Above, the stairwell twists and turns up into darkness.\n";
}


public void
create_gondor()
{
    set_short("A narrow stairwell");
    set_long(stairwell_long_desc() + long_extratext());

    prison_add_items();
    stairwell_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage"}), 
        stairwell_long_desc() + long_extratext());
    add_item(({"corridor"}), "You would need to descend the stairs to "
        + "get a closer look.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "second_stair4",        "up");
    add_exit(IGARD_DEEP_PRISON + "lev2_hall6",           "down");

    reset_room();
}

