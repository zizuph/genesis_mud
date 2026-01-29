#pragma strict_types

#include "defs.h"

inherit NEWALKBASE;

public void
create_room()
{
    extra = "The walkway dead-ends here, with the top of the " +
        "eastern outer wall cutting across the walk to " +
        "intersect with the wall on your south." +
        "The top of a narrow stone staircase lays " +
        "at the edge of the walkway, descending diagonally "+
        "down the southern wall of the courtyard.";


    create_walk("southeast");

    add_exit(RUIN + "ne_walk_4", "west");
    add_exit(RUIN + "ne_court_stairs", "down");
}
