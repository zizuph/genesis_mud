/*
 *   /d/Gondor/ithilien/poros/manor/westhall1.c
 *
 *   A hall in the manor that serves as a hidden base for corsairs.
 *
*   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

void
create_manor()
{
    set_area("hallway");
    set_extraline("The hallway comes to an intersection here. The main "
      + "hallway continues to the west and east, while a smaller "
      + "passage leads to the south.");

    add_exit(POROS_DIR + "manor/westhall2", "west", 0, 1);
    add_exit(POROS_DIR + "manor/foyer", "east", 0, 1);
    add_exit(POROS_DIR + "manor/westhall3", "south", 0, 1);

    add_hallway();
    add_rubble();
    add_furniture();
    add_carpet();
}
