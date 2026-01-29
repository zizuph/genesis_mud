/*
 *  WALL_TUNNEL_THREE + "swt1.c"
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
    return "This section of the tunnel is somewhere in the southwestern "
    + "part of the ring wall on the third level. The tunnel ends abruptly "
    + "to the northwest at a wall of raw mountain stone.\n";
}


public void
create_gondor()
{
    set_short("A dead end in the southwestern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());
    add_item(({"stone", "mountain stone", "raw stone", "raw mountain stone"}),
        "The stone of the northwest wall is unworked. It is as if the "
        + "builders of the ring wall simply decided to halt excavation when "
        + "they reached the southwest face of the mountain.\n");
    add_item(({"northwest wall", "wall", "wall of stone"}), "The wall to "
        + "southwest brings an abrupt halt to your journey through the "
        + "tunnel. The raw stone suggests you have at last reached the "
        + "southeastern face of the mountain above Isengard.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_THREE + "swt2.c",      "southeast");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



