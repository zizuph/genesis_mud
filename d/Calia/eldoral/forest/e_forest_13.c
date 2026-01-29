#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_special(BOULDERS, "north");
    create_forest();    

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"boulders"}));

    add_exit(FOREST + "e_forest_14", "east");
    add_exit(FOREST + "e_forest_11", "south");
    add_exit(FOREST + "e_forest_12", "west");
}
