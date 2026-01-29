/*
 *  WALL_TUNNEL_ONE + "st1.c"
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
    return "This section of the tunnel is somewhere in the southern "
    + "part of the ring wall on the ground level.\n";
}


public void
create_gondor()
{
    set_short("A tunnel in the southern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());

    add_item(({"west wall", "wall", "wall of stone"}), "The wall to "
        + "the west brings an abrupt halt to your journey through the "
        + "tunnel.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_ONE + "st2.c",                "east");
    add_exit(WALL_FLOOR_ONE  + "1_archroom_2.c",       "west");

    reset_room();
}


