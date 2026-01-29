#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(SHRINE, "south");
    create_forest();
    add_exit(FOREST + "s_forest_5", "north");
    add_exit(FOREST + "s_forest_16", "east");
    add_exit(FOREST + "shrine_1", "south");
    add_exit(FOREST + "s_forest_14", "west");
}
