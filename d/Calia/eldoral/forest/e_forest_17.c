#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BOULDERS, "south");
    create_forest();    

    add_exit(FOREST + "e_forest_20", "north");
    add_exit(FOREST + "e_forest_18", "east");
    add_exit(FOREST + "e_forest_16", "west");
}
