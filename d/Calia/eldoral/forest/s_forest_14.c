#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(CATH_RUBBLE, "north and west");
    create_forest();
    add_exit(FOREST + "s_forest_15", "east");
    add_exit(FOREST + "s_forest_23", "south");
}
