#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("north");
    create_special(CATH_RUBBLE, "east");
    create_forest();
    add_exit(FOREST + "s_forest_3", "west");
    add_exit(FOREST + "s_forest_12", "south");
}
