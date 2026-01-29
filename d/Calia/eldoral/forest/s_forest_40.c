#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SHRINE, "north");
    create_forest();

    add_exit(SHORE + "shore5", "east", "@@shore_msg");
    add_exit(SHORE + "shore4", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_39", "west");
}
