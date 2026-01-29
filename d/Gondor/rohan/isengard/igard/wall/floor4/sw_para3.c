/*
 *  WALL_FLOOR_FOUR + "sw_para3.c"
 *
 *  Parapet on fourth floor of Isengard ring wall.
 *
 *  Last modified by Alto, 01 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "This section of the ring wall looks to the southwest, where "
    + "the Misty Mountains rise high into the southwestern sky. "
    + "The parapet extends to the northwest, and a stairwell "
    + "leads up to a higher parapet.\n";
}


public void
create_gondor()
{
    set_short("A parapet atop the southwestern ring wall");
    set_long(parapet_long_desc() + long_extratext());

    sky_add_items();
    parapet_add_items();

    add_item(({"room", "area", "surroundings", "place", "parapet",
        "stone parapet", "section", "landscape"}), 
        parapet_long_desc() + long_extratext());

    add_item(({"stairwell", "stairs", "steps", "stair", "wide stairwell"}), 
        "The wide stairwell leads up to a higher parapet.\n");

    add_parapet_tells();

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WALL_FLOOR_FOUR + "sw_para3t.c",      "up");
    add_exit(WALL_FLOOR_FOUR + "sw_para2.c",       "northwest");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



