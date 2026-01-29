/*
 *   /d/Gondor/ithilien/poros/manor/westhall2.c
 *
 *   A hallway in the manor that serves as a hidden base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

void  reset_room();

object  *Corsair = allocate(2);

void
create_manor()
{
    set_area("hallway");
    set_extraline("The hallway runs to the east, and leads down a "
      + "steep flight of stairs to the west. To the north, the hallway enters "
      + "into a large room.");

    add_exit(POROS_DIR + "manor/cellar", "down", 0, 1);
    add_exit(POROS_DIR + "manor/dininghall", "north", 0, 1);
    add_exit(POROS_DIR + "manor/westhall1", "east", 0, 1);

    add_hallwayb();
    add_rubble();
    add_furniture();
    add_carpet();
    add_stairs();

    reset_room();
}

void
reset_room()
{
    int  i = sizeof(Corsair);

    while (i--)
    {

    if (!objectp(Corsair[i]))
    {
      Corsair[i] = clone_object(POROS_DIR + "npcs/corsair");
      Corsair[i]->arm_me();
      Corsair[i]->move_living("down", TO);
    }
    }
}
