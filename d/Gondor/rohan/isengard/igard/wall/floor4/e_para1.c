/*
 *  WALL_FLOOR_FOUR + "e_para1.c"
 *
 *  Parapet on fourth floor of Isengard ring wall.
 *
 *  Last modified by Alto, 01 October 2001
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

string
long_extratext()
{
    return "This section of the ring wall looks to the east, where "
    + "the plains of Rohan can be seen over the foothills of the "
    + "Misty Mountains. The parapet extends to the north, and a "
    + "stairwell leads up to a higher parapet.\n";
}


public void
create_gondor()
{
    set_short("A parapet atop the eastern ring wall");
    set_long(parapet_long_desc() + long_extratext());

    sky_add_items();
    parapet_add_items();

    add_item(({"room", "area", "surroundings", "place", "parapet",
        "stone parapet", "section", "landscape"}), 
        parapet_long_desc() + long_extratext());

    add_item(({"stairwell", "stairs", "steps", "stair", "wide stairwell"}), 
        "The wide stairwell leads up to a higher parapet.\n");
    add_item(({"plains", "rohan", "plains of rohan", "sea"}), "A great and "
        + "sweeping plain of wind-swept grass unrolls to the east. "
        + "This is the land of Rohan, where the Horse Lords rule.\n");
    add_item(({"grass"}), "There is an endless sea of it rolling away to "
        + "the east.\n");
    add_item(({"foothills", "foothill"}), "The Wizard's Vale lies between "
        + "several of the southern Misty Mountains. Some of their foothills "
        + "fork to the west, north and east of Nan Curunir.\n");

    add_parapet_tells();

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WALL_FLOOR_FOUR + "e_para1t.c",      "up");
    add_exit(WALL_FLOOR_FOUR + "e_para2.c",       "north");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



