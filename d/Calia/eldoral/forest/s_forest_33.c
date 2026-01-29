#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("east and south");
    create_special(SHRINE, "west");
    create_forest();

    add_exit(FOREST + "s_forest_24", "north");
    add_exit(SHORE + "shore6", "east", "@@shore_msg");
    add_exit(SHORE + "shore5", "south", "@@shore_msg");
}
