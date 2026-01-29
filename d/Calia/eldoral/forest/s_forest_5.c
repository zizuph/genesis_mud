#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_special(CATH_RUBBLE, "west");
    create_forest();
    add_exit(FOREST + "s_forest_6", "east");
    add_exit(FOREST + "s_forest_15", "south");
}
