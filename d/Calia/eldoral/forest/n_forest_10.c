#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("south");
    create_forest();
    
    add_exit(FOREST + "n_forest_7", "north");
    add_exit(FOREST + "n_forest_11", "east");
    add_exit(FOREST + "n_forest_9", "west");
}
