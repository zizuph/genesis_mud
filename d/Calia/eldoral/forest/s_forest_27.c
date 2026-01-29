#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "north");
    create_forest();

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"building", "ruins", 
        "rubble"}));

    add_exit(FOREST + "s_forest_28", "east");
    add_exit(FOREST + "s_forest_34", "south");
    add_exit(FOREST + "s_forest_26", "west");
}
