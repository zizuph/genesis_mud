#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BUILD_RUINS, "east");
    create_forest();

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"building", "ruins", 
        "rubble"}));

    add_exit(FOREST + "s_forest_9", "north");
    add_exit(FOREST + "s_forest_26", "south");
    add_exit(FOREST + "s_forest_18", "west");
}
