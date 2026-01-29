#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_forest();    

    add_exit(FOREST + "e_forest_26", "north");
    add_exit(FOREST + "e_forest_24", "east");
    add_exit(FOREST + "e_forest_21", "south");
}
