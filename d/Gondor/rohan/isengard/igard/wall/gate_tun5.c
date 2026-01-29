/*
 *  IGARD_WALL + "gate_tun5.c"
 *
 *  Tunnel behind the southern gate of Isengard.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "You are presently somewhere near the northern gate of "
    + "of the tunnel.\n";
}


public void
create_gondor()
{
    set_short("Near the northern gate of the tunnel");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());

    add_tunnel_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_WALL + "gate_tun4",        "south");
    add_exit(IGARD_WALL + "gate_tun6",        "north");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

