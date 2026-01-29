#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_ravine();
    create_special(BUILD_RUINS, "north");
    create_forest();

    add_exit(FOREST + "n_forest_8", "east");
    add_exit(FOREST + "n_forest_10", "south");
    add_exit(FOREST + "n_forest_6", "west");
}
