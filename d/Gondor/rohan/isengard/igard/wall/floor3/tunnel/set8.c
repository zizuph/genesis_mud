/*
 *  WALL_TUNNEL_THREE + "set8.c"
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
public int         move_player();

string
long_extratext()
{
    return "Although it is difficult to keep your bearings in this "
    + "place, you believe this section of the tunnel is somewhere in "
    + "the southeastern part of the ring wall on the third level. "
    + "A narrow stone walkway leads to the northeast.\n";
}


public void
create_gondor()
{
    set_short("A tunnel in the southeastern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();
    walkway_add_items();

    add_cmd_item(({"walkway", "narrow walkway", "the walkway", 
        "the narrow walkway", "stone walkway", "the stone walkway"}), 
        "cross", &cross_walkway());

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());

    add_tunnel_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_THREE + "set7.c",       "southwest");

    reset_room();
}


int
move_player()
{
    tell_room(environment(TP), QCTNAME(TP) + " leaves across the "
        + "narrow stone walkway.\n", ({TP}));
    tell_room(WALL_TUNNEL_THREE + "set9", QCNAME(TP) + " arrives from the "
        + "other end of the narrow stone walkway.\n");

    TP->move_living("M", WALL_TUNNEL_THREE + "set9", 1, 0);
    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



