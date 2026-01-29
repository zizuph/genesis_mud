/*
 *  IGARD_DEEP_PRISON + "lev2_hall2.c"
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
    return "To the north and south, doors with iron bars rest before "
    + "darkened doorways. Their locks have been shattered and broken, "
    + "and the doors hang open upon their hinges.\n";
}


public void
create_gondor()
{
    set_short("A dank and musty corridor");
    set_long(hallway_long_desc() + long_extratext());

    prison_add_items();
    hallway_add_items();

    add_item(({"room", "area", "surroundings", "place", "passage", "corridor"}), 
        hallway_long_desc() + long_extratext());


    add_hallway_tells();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(IGARD_DEEP_PRISON + "lev2_hall1",          "west");
    add_exit(IGARD_DEEP_PRISON + "lev2_hall3",          "east");

    add_exit(IGARD_DEEP_PRISON + "lev2_cell2n",         "north");
    add_exit(IGARD_DEEP_PRISON + "lev2_cell2s",         "south");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))

     start_room_tells();

}
