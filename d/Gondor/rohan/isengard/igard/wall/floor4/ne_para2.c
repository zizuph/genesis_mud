/*
 *  WALL_FLOOR_FOUR + "ne_para_2.c"
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

static object *Archer   = allocate(3);

string
long_extratext()
{
    return "This section of the ring wall looks to the northeast, where "
    + "Fangorn forest can be seen through the foothills of the Misty "
    + "Mountains. The parapet extends to the northwest and southeast, and "
    + "a stairwell leads down into the ring wall.\n";
}


public void
create_gondor()
{
    set_short("A parapet atop the northeastern ring wall");
    set_long(parapet_long_desc() + long_extratext());

    sky_add_items();
    parapet_add_items();

    add_item(({"room", "area", "surroundings", "place", "parapet",
        "stone parapet", "section", "landscape"}), 
        parapet_long_desc() + long_extratext());

    add_item(({"stairwell", "stairs", "steps", "stair", "wide stairwell"}), 
        "The wide stairwell descends into the ring wall.\n");
    add_item(({"forest", "fangorn", "forest of fangorn", "fangorn forest",
        "trees", "mass"}), 
        "The great dark mass of trees to the northeast is Fangorn forest, "
        + "one of the oldest remaining in Middle Earth. It is rumoured that "
        + "strange giants, known as Ents, live under its mysterious "
        + "leaves.\n");
    add_item(({"leaf", "leaves"}), "From this distance, it is impossible "
        + "to make out individual leaves, but the colour of the trees "
        + "suggests they are covered with them.\n");

    add_parapet_tells();

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WALL_FLOOR_FOUR + "ne_para1.c",       "northwest");
    add_exit(WALL_FLOOR_FOUR + "ne_para3.c",       "southeast");
    add_exit(WALL_TUNNEL_THREE + "net5.c",         "down");

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Archer,  IGARD_NPC + "igard_archer",  -1.0);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



