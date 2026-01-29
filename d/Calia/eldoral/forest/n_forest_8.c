#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_ravine();
    create_special(BUILD_RUINS, "north and east");
    create_forest();

    add_exit(FOREST + "n_forest_11", "south");
    add_exit(FOREST + "n_forest_7", "west");
}
