#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();

    add_exit(FOREST + "s_forest_32", "north");
    add_exit(FOREST + "s_forest_40", "east");
    add_exit(SHORE + "shore3", "south", "@@shore_msg");
    add_exit(FOREST + "s_forest_38", "west");
}
