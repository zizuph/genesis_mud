/*
 *  WALL_FLOOR_FOUR + "s_para3.c"
 *
 *  Parapet overlooking the southern gate of Isengard.
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
    return "This section of the ring wall looks to the south, where "
    + "a great highway leads away from Isengard toward the Gap of Rohan. "
    + "Directly below you is the great southern gate, the only entrance "
    + "or exit from the fortification of Isengard. A stairwell ascends from "
    + "below and continues upward to a higher parapet.\n";

}


public void
create_gondor()
{
    set_short("A parapet atop the southern ring wall");
    set_long(parapet_long_desc() + long_extratext());

    sky_add_items();
    parapet_add_items();

    add_item(({"room", "area", "surroundings", "place", "parapet",
        "stone parapet", "section", "landscape"}), 
        parapet_long_desc() + long_extratext());

    add_item(({"stairwell", "stairs", "steps", "stair"}), "The stairwell "
        + "opens in the middle of the parapet and rises in spiral fashion "
        + "to the next parapet.\n");
    add_item(({"highway", "road", "street"}), "A wide highway runs "
        + "from the distant south right up to the great southern gate "
        + "directly below. It seems well-crafted for the passage of "
        + "heavy carts and horses.\n");
    add_item(({"gap of rohan"}), "The gap is a large open area between "
        + "the Misty Mountains to the north and the White Mountains to "
        + "the south. Isengard looks down upon the Gap of Rohan much as a "
        + "majestic bird of prey watches a field for stray mice.\n");
    add_item(({"white mountain", "white mountains"}), "The White Mountains, "
        + "on the southern edge of the Gap of Rohan, can just barely be "
        + "made out to the south.\n");
    add_item(({"rohan"}), "The land of the Horse Lords lies to the "
        + "southeast. Although little of it can be seen from this section "
        + "of the wall, it is rumoured to be a seemingly endless ocean "
        + "of grass.\n");
    add_item(({"gate", "southern gate", "great southern gate", "entrance",
        "exit"}), "As it is directly below you, it is very difficult to "
        + "discern without leaning far over the ramparts. The strong wind "
        + "here renders that kind of curiosity extremely dangerous.\n");

    add_parapet_tells();

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WALL_FLOOR_FOUR + "s_para4.c",        "up");
    add_exit(WALL_FLOOR_FOUR + "s_para2.c",        "down");

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



