#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "west");
    create_forest();    

    add_exit(FOREST + "e_forest_33", "north");
    add_exit(FOREST + "e_forest_32", "east");
    add_exit(FOREST + "e_forest_29", "south");
}
