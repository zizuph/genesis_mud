#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(SHRINE, "east");
    create_forest();

    add_exit(FOREST + "s_forest_23", "north");
    add_exit(FOREST + "s_forest_39", "south");
    add_exit(FOREST + "s_forest_31", "west");
}
