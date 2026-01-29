#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();

    add_exit(FOREST + "s_forest_31", "north");
    add_exit(FOREST + "s_forest_39", "east");
    add_exit(SHORE + "shore2", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_37", "west");
}
