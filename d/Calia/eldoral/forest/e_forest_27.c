#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();    

    add_exit(FOREST + "e_forest_30", "north");
    add_exit(FOREST + "e_forest_28", "east");
    add_exit(FOREST + "e_forest_24", "south");
    add_exit(FOREST + "e_forest_26", "west");
}
