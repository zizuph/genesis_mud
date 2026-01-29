#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    extra = "A long heap of rubble rises to the west, seemingly the " +
        "remains of very tall tower that collapsed countless years " +
        "before. It also crushed a small stone structure of " +
        "some sort, which now lies beneath the remains of the " +
        "tower to the south. ";

    create_special(TOW_RUBBLE, "south");
    create_forest();
    
    add_item(({"tower", "rubble"}),
        "These appear to be the remains of what was once a tower. And " +
        "an extremely tall one, judging by the size of it.\n");
    add_item(({"structure", "remains", "stone structure"}),
        "Quite possibly, the shattered stone was once a small house " +
        "or stable of some sort, but that's a wild guess, as the " +
        "weight of the tower has obliterated everything but the general " +
        "shape of its foundation.\n");

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"structure", "remains",
        "stone structure"}));

    add_exit(FOREST + "n_forest_1", "north");
    add_exit(FOREST + "n_forest_5", "east");
}
