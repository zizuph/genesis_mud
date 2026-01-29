#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();
    add_exit(FOREST + "s_forest_13", "north");
    add_exit(FOREST + "s_forest_22", "east");
    add_exit(FOREST + "s_forest_30", "south");
    add_exit(FOREST + "s_forest_20", "west");
}
