#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(CATH_RUBBLE, "north");
    create_forest();
    add_exit(FOREST + "s_forest_23", "east");
    add_exit(FOREST + "s_forest_31", "south");
    add_exit(FOREST + "s_forest_21", "west");
}
