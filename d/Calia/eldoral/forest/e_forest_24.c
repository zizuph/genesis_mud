#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(SHRINE, "south");
    create_forest();    

    add_exit(FOREST + "e_forest_27", "north");
    add_exit(FOREST + "e_forest_25", "east");
    add_exit(FOREST + "shrine_3", "south");
    add_exit(FOREST + "e_forest_23", "west");
}
