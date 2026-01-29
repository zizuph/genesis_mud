#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_forest();    

    add_exit(FOREST + "e_forest_19", "north");
    add_exit(FOREST + "e_forest_17", "east");
    add_exit(FOREST + "e_forest_15", "south");
}
