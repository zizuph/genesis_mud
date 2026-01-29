/*
 *  WALL_TUNNEL_ONE + "nt5.c"
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
public int         leave_room();

string
long_extratext()
{
    return "Although it is difficult to keep your bearings in this "
    + "place, you believe this section of the tunnel is somewhere in "
    + "the northern part of the ring wall on the ground level. A threadbare "
    + "tapestry hangs on the south wall.\n";
}


public void
create_gondor()
{
    set_short("A tunnel in the northern part of the ring wall");
    set_long(tunnel_long_desc() + long_extratext());

    wall_add_items();

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), 
        tunnel_long_desc() + long_extratext());

    add_item(({"south wall"}), "The south wall is mostly covered with a large "
        + "threadbare tapestry.\n");
    add_item(({"tapestry", "large tapestry", "threadbare tapestry", 
        "large threadbare tapestry"}), "The tapestry conceals something on "
        + "the wall. You will need to move it to see what is behind.\n");

    add_cmd_item(({"tapestry", "large tapestry", "threadbare tapestry", 
        "large threadbare tapestry"}), "move", &leave_room());

    add_tunnel_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_ONE + "nt4.c",      "east");
    add_exit(WALL_TUNNEL_ONE + "nt6.c",      "west");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


int
leave_room()
{
    write("You move aside the tapestry and silently slip behind it.\n");
    say(QCTNAME(TP) + " slips silently behind the tapestry.\n");
    tell_room(WALL_FLOOR_ONE + "1_archroom_2c.c", QCTNAME(TP) + " slips silently "
        + "into the room from behind the tapestry.\n");

    TP->move_living("M", WALL_FLOOR_ONE + "1_archroom_2c.c", 1, 0);

    return 1;
}


