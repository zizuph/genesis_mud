#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_ravine();
    create_special(BUILD_RUINS, "west");
    create_forest();    

    add_exit(SHORE + "shore23", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_31", "south");
}
