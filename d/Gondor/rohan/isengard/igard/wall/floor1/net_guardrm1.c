/*
 *  IGARD_WALL + "net_guardrm1.c"
 *
 *  Guardroom at a gate in the ring wall of Isengard.
 *
 *  Last modified by Alto, 28 September 2001
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

static object *Orc   = allocate(2);
static object *Orc2  = allocate(1);

string
long_extratext()
{
    return "The doorway leads southeast back into the tunnel.\n";
}


public void
create_gondor()
{
    set_short("A small guardroom");
    set_long(guardrm_long_desc() + long_extratext());

    wall_add_items();
    guardrm_add_items();

    add_item(({"room", "area", "surroundings", "place", "guardroom"}), 
        guardrm_long_desc() + long_extratext());

    add_item(({"gate tunnel", "tunnel"}), "Outside the doorway is the "
        + "tunnel inside one of the inner ring wall gates of Isengard.\n");

    add_fire_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WALL_TUNNEL_ONE + "net_gate1.c",        "southeast");

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Orc,  IGARD_NPC + "igard_orc",  -1.0);
    clone_npcs(Orc2, IGARD_NPC + "igard_orc2", -1.0);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



