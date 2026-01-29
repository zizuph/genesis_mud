#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_ravine();
    create_forest();

    add_exit(FOREST + "n_forest_3", "east");
    add_exit(FOREST + "n_forest_5", "south");
    add_exit(FOREST + "n_forest_1", "west");
}
