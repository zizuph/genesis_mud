#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(CATH_RUBBLE, "north and east");
    create_forest();
    add_exit(FOREST + "s_forest_21", "south");
    add_exit(FOREST + "s_forest_12", "west");
}
