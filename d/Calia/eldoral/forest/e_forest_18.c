#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    create_shore("north and east");
    create_special(BOULDERS, "south");
    create_forest();    

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"boulders"}));

    add_exit(SHORE + "shore17", "north", "@@shore_msg");
    add_exit(SHORE + "shore16", "east", "@@shore_msg");
    add_exit(FOREST + "e_forest_17", "west");
}
