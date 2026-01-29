/*
 *  WALL_TUNNEL_TWO + "nwt10.c"
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
    return "This section of the tunnel is somewhere in the northwestern "
    + "part of the ring wall on the second level. The tunnel ends abruptly "
    + "to the southwest at a wall of raw mountain stone. A wide stairwell "
    + "along one wall of the tunnel leads upward.\n";
}


public void
create_gondor()
{
    set_short("A dead end in the northwestern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());
    add_item(({"stone", "mountain stone", "raw stone", "raw mountain stone"}),
        "The stone of the southwest wall is unworked. It is as if the "
        + "builders of the ring wall simply decided to halt excavation when "
        + "they reached the northwest face of the mountain.\n");
    add_item(({"southwest wall", "wall", "wall of stone"}), "The wall to "
        + "southwest brings an abrupt halt to your journey through the "
        + "tunnel. The raw stone suggests you have at last reached the "
        + "northwestern face of the mountain above Isengard.\n");
    add_item(({"stairwell", "stairs", "steps", "step", "stair"}), "The "
        + "wide stairwell leads up to the third level of the ring "
        + "wall.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_TWO + "nwt9.c",      "northeast");
    add_exit(WALL_TUNNEL_THREE + "nwt10.c",          "up");

    reset_room();
}


