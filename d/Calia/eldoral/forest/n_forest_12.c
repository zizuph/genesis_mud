#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("south");
    create_special(BUILD_RUINS, "north");
    create_forest();
    
    add_exit(FOREST + "e_forest_29", "east");
    add_exit(FOREST + "n_forest_11", "west");
}
