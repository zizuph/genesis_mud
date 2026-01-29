/*   /d/Gondor/ithilien/poros/manor/northhall.c
 *
 *   A hallway in the manor that hides a corsair base.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

object  *Corsair = allocate(2);

public void
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

void
create_manor()
{
    set_area("hallway");
    set_extraline("The hallway comes to an intersection here. However the "
      + "north and east passageways are collapsed, leaving the only "
      + "exits to the west and south.");

    add_exit(POROS_DIR + "manor/barracks", "west", 0, 1);
    add_exit(POROS_DIR + "manor/southhall", "south", 0, 1);

    add_hallwayb();
    add_rubble();
    add_passage();
    add_furniture();

    reset_room();
}
