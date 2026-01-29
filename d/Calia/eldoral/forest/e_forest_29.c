#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_forest();    

    add_exit(FOREST + "e_forest_31", "north");
    add_exit(FOREST + "e_forest_30", "east");
    add_exit(FOREST + "e_forest_26", "south");
    add_exit(FOREST + "n_forest_12", "west");
}
