#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();

    add_exit(FOREST + "s_forest_28", "north");
    add_exit(FOREST + "s_forest_36", "east");
    add_exit(SHORE + "shore31", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_34", "west");
}
