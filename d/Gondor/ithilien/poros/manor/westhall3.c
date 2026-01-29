/*
 *   /d/Gondor/ithilien/poros/manor/westhall3.c
 *
 *   A hall in the manor that serves as the hidden base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

void
create_manor()
{
    set_area("narrow hallway");
    set_extraline("The hallway continues to the north, and leaves the manor "
      + "through an arched doorway to the south.");

    add_exit(POROS_DIR + "manor/westhall1", "north", 0, 1);
    add_exit(POROS_DIR + "manor/garden", "south", 0, 1);

    add_hallway();
    add_rubble();
    add_furniture();
    add_carpet();
}
