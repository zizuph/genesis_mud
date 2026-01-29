#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    extra = "A long heap of rubble rises to the west, seemingly the " +
        "remains of very tall tower that collapsed countless years " +
        "before, falling to its death upon the ground here. The " +
        "steepness of its square sides, and the slippery lichen which " +
        "now covers its surface, makes it an impossible obstacle to " +
        "climb over. ";

    create_ravine();
    create_forest();
    
    add_item(({"tower", "rubble"}),
        "These appear to be the remains of what was once a tower. And " +
        "an extremely tall one, judging by the size of it.\n");

    add_exit(FOREST + "n_forest_2", "east");
    add_exit(FOREST + "n_forest_4", "south");
}
