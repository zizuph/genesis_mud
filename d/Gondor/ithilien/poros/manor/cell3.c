/*
 *   /d/Gondor/ithilien/poros/manor/cell3.c
 *
 *   A prisoner cell in the manor that serves as a base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

//    Prototypes:
void  reset_room();

//    Global Variables:
object  *Prisoner = allocate(2 +random(6));

void
create_manor()
{
    set_area("cell");
    set_extraline("The cell is a dank, wet, and smelly place. A thin "
      + "layer of dirty straw is all that lines the hard stone floor. "
      + "Through the lone door is the only exit.");

    add_item(({"straw", "dirty straw"}), BSN(
        "Besides dirt and human waste, some traces of blood can be "
      + "seen in places on the straw."));

    add_item(({"cell", "ground", "floor"}), BSN(
        "The walls and floor of the cell are all very sturdy. You "
      + "estimate there is little hope of escape for the prisoners "
      + "that are kept here, who will likely end up as slaves, "
      + "or worse..."));

    clone_object(POROS_DIR + "obj/door_cell3b")->move(TO);

    reset_room();
}

void
reset_room()
{
    int  i = sizeof(Prisoner);

    while (i--)
    {
      if (!objectp(Prisoner[i]))
      {
        Prisoner[i] = clone_object(POROS_DIR + "npcs/prisoner");
        Prisoner[i]->move_living("down", TO);
      }
    }
}
