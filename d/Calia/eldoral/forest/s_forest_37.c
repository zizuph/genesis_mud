#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("south");
    create_forest();

    add_exit(FOREST + "s_forest_30", "north");
    add_exit(FOREST + "s_forest_38", "east");
    add_exit(SHORE + "shore1", "south", "@@woods_msg");
    add_exit(FOREST + "s_forest_36", "west");
}
