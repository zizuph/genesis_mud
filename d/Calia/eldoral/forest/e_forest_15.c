#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_wall("west");
    create_special(BOULDERS, "east");
    create_forest();    

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"boulders"}));

    add_exit(FOREST + "e_forest_16", "north");
    add_exit(FOREST + "e_forest_12", "south");
}
