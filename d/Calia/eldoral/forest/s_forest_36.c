#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();

    add_exit(FOREST + "s_forest_29", "north");
    add_exit(FOREST + "s_forest_37", "east");
    add_exit(SHORE + "shore32", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_35", "west");
}
