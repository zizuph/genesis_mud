#pragma strict_types

#include "defs.h"

inherit NEWALKBASE;

public void
create_room()
{
    extra = "The walkway dead-ends here, with the top of the " +
        "northern outer wall cutting across the walk to " +
        "intersect with the wall on your west.";
    create_walk("northwest");

    add_exit(RUIN + "ne_walk_2", "south");
}
