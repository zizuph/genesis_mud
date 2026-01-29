#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();

    add_exit(FOREST + "s_forest_20", "north");
    add_exit(FOREST + "s_forest_30", "east");
    add_exit(FOREST + "s_forest_36", "south");
    add_exit(FOREST + "s_forest_28", "west");
}
