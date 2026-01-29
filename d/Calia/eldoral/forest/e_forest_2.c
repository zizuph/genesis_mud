#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();    

    add_exit(FOREST + "e_forest_4", "north");
    add_exit(FOREST + "e_forest_3", "east");
    add_exit(FOREST + "e_forest_1", "south");
    add_exit(FOREST + "s_forest_7", "west");
}
