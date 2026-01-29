#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "south");
    create_forest();

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"building", "ruins", 
        "rubble"}));

    add_exit(FOREST + "s_forest_3", "north");
    add_exit(FOREST + "s_forest_12", "east");
    add_exit(FOREST + "s_forest_10", "west");
}
