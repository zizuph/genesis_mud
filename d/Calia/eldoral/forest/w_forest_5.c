#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_cliff();
    create_forest();

    add_exit(FOREST + "w_forest_4", "north");
    add_exit(FOREST + "w_forest_6", "east");
    add_exit(FOREST + "w_forest_8", "south");
}
