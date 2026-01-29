#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(SHRINE, "east");
    create_forest();
    add_exit(FOREST + "s_forest_14", "north");
    add_exit(FOREST + "s_forest_32", "south");
    add_exit(FOREST + "s_forest_22", "west");
}
