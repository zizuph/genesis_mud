#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_ravine();
    create_special(BUILD_RUINS, "east");
    create_forest();

    add_exit(FOREST + "n_forest_6", "south");
    add_exit(FOREST + "n_forest_2", "west");
}
