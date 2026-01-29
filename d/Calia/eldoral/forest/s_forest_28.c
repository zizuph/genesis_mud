#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "north");
    create_forest();

    add_exit(FOREST + "s_forest_29", "east");
    add_exit(FOREST + "s_forest_35", "south");
    add_exit(FOREST + "s_forest_27", "west");
}
