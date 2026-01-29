/*   /d/Gondor/ithilien/poros/manor/barracks.c
 *
 *   A room inside the manor that is used as a hidden base by corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

//    Prototypes:
void  reset_room();

//    Global Variables:
object  *Corsair = allocate(6);

void
create_manor()
{
    set_area("large room");
    set_extraline("The room appears to be a makeshift barracks of sorts. "
      + "A passage to the west is collapsed, and an open archway leads "
    + "southwest. To the northwest is a door, while the hall leaves the room "
      + "to the east.");

    add_exit(POROS_DIR + "manor/dininghall", "southwest", 0, 1);
    add_exit(POROS_DIR + "manor/northhall", "east", 0, 1);

    add_item(({"barracks", "floor", "ground"}), BSN(
        "It appears this is the room used as the main living quarters of "
      + "the corsairs based in this old manor. You notice as well as "
      + "bedrolls, that some other gear is stowed here also. The room "
      + "is stuffy and stale, and smells of unclean, sweaty bodies."));

    add_item(({"bedrolls"}), BSN(
        "They are rolled out along the walls, providing places for the "
      + "corsairs to sleep."));

    add_item(({"gear"}), BSN(
        "You can see various pieces of corsair gear lying around the "
      + "room. Nothing strikes you as having significant value."));

    add_passage();

    clone_object(POROS_DIR + "obj/door1")->move(TO);

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
