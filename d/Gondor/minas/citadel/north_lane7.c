/*
 *  /d/Gondor/minas/citadel/north_lane7.c
 *
 *  Lane running around the west perimeter of the White Tower
 *
 *  Alto, 21 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_gondor()
{
    set_short("A lane west of the White Tower");
    set_long("This is a small lane running around the base of the "
        + "White Tower of Ecthelion. On the inner side, the lane is "
        + "bounded by the smooth cool stone of the tower itself, "
        + "while on the outer side it is contained by a long curved "
        + "hedge. The lane leads southeast and northeast from here.\n");

    add_exit(INNER_MINAS + "/citadel/north_lane6", "northeast", 0, 1);
    add_exit(INNER_MINAS + "/citadel/south_lane6", "southeast", 0, 1);

    add_prop(ROOM_I_INSIDE, 0);

    add_lane_items();

    set_tell_time(120);

    add_lane_tells();

    reset_room();
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}




