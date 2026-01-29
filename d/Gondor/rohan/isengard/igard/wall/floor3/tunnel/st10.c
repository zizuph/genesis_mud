/*
 *  WALL_TUNNEL_THREE + "st10.c"
 *
 *  Tunnel on first floor of Isengard ring wall.
 *
 *  Last modified by Alto, 29 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "Although it is difficult to keep your bearings in this "
    + "place, you believe this section of the tunnel is somewhere in "
    + "the southern part of the ring wall on the third level. A "
    + "wide stairwell leads upwards.\n";
}


public void
create_gondor()
{
    set_short("A tunnel in the southern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());

    add_item(({"stairs", "stair", "stairwell", "wide stairwell", "steps"}),
        "A wide stairwell rises upwards along the wall. Faint light can "
        + "be seen streaming down from above.\n");
    add_item(({"light"}), "Faint light illuminates the top of the "
        + "stairwell.\n");

    add_tunnel_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_THREE + "st9.c",         "west");
    add_exit(WALL_TUNNEL_THREE + "st11.c",        "east");
    add_exit(WALL_FLOOR_FOUR + "s_para1.c",       "up");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



