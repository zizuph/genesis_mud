/*
 *  WALL_TUNNEL_THREE + "nt6.c"
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
inherit IGARD_LIB + "quest_funcs.c";

public void        create_gondor();
public int         test_quest();

static object  Troop;

string
long_extratext()
{
    return "Although it is difficult to keep your bearings in this "
    + "place, you believe this section of the tunnel is somewhere in "
    + "the northern part of the ring wall on the third level. A "
    + "wide stairwell leads upwards.\n";
}


public void
create_gondor()
{
    set_short("A tunnel in the northern part of the ring wall");
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

    add_exit(WALL_TUNNEL_THREE + "nt5.c",       "east");
    add_exit(WALL_TUNNEL_THREE + "nt7.c",       "west");
    add_exit(WALL_FLOOR_FOUR + "n_para2.c",       "up");

    add_item(({"tapestry", "tapestries"}), "Hanging from one of the walls is a " 
        + "dull tapestry. Its yellow cloth has a loose weave that is shot "
        + "through with bronze thread. The tapestry looks rather dusty.\n");

    add_cmd_item(({"tapestry", "large tapestry", "threadbare tapestry", 
        "large threadbare tapestry"}), "move", &test_quest());

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

public void
reset_room()
{
    if (!objectp(Troop))
    {
        Troop = clone_object(IGARD_NPC + "igard_uruk_lead2.c");
        Troop->set_restrain_path(WALL_TUNNEL_THREE);
        Troop->arm_me();
        Troop->move_living("down", TO);
        Troop->add_3_orcs(3);
    }
}


public int
test_quest()
{
    object ambush;

    if (!SIW1 && !SIW2 && !SIW3 && !SIW4 && !SIW5 && !SIW6 && !SIW7)
    {
        return 1;
    }

    if (!SIW6)
    {
        ambush = clone_object(IGARD_QUEST_OBJ + "quest_ambush");
        ambush->move(TO);
        return 1;
    }

    TP->remove_prop(SENT_IGARD_WALL6);
    TP->add_prop(FINISHED_IGARD_WALL, 1);
    igard_stage_check();
    return 1;
}

