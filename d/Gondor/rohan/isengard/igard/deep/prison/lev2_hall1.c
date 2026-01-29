/*
 *  IGARD_DEEP_PRISON + "lev2_hall1.c"
 *
 *  Corridor in the prisons below Isengard.
 *
 *  Last modified by Alto, 11 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "prison_funcs.c";

public void        create_gondor();

string
long_extratext()
{
    return "A narrow stairwell leads down. Looking up the corridor, "
    + "to the east, you see numerous doorways on either side of the "
    + "passage.\n";
}


public void
create_gondor()
{
    set_short("A dank and musty corridor");
    set_long(hallway_long_desc() + long_extratext());

    prison_add_items();
    stairwell_add_items();
    hallway_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage", "corridor"}), 
        hallway_long_desc() + long_extratext());

    add_item(({"doorway", "doorways"}), "The corridor leading to the east is "
        + "girded by numerous gaping doorways on both sides.\n");
    add_item(({"stairwell"}), "A narrow stairwell descends rapidly into the "
        + "shadows below.\n");

    remove_item("scratch");
    remove_item("bar");
    remove_item("socket");
    remove_item("lock");
    remove_item("hinge");

    add_hallway_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "third_stair1",        "down");
    add_exit(IGARD_DEEP_PRISON + "lev2_hall2",          "east");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))

     start_room_tells();

}
