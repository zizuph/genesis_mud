/*
 *   /d/Gondor/ithilien/poros/manor/dininghall.c
 *
 *   The room inside the manor that serves as a hidden base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

//    Prototypes:
void  reset_room();

//    Global Variables:
object  Mate,
       *Corsair = allocate(4);

void
create_manor()
{
    set_area("large dining hall");
    set_extraline("In the center of the hall stands a huge banquet table. "
      + "A chandelier hangs above the table, and a large fireplace rests "
      + "along the western wall. A arched doorway leads to the northeast, "
      + "while other passages lead to the east and south.");

    add_exit(POROS_DIR + "manor/barracks", "northeast", 0, 1);
    add_exit(POROS_DIR + "manor/kitchen", "east", 0, 1);
    add_exit(POROS_DIR + "manor/westhall2", "south", 0, 1);

    add_item(({"dining hall", "floor", "ground", "hall"}), BSN(
        "The dining hall shows signs of recent use. Plates for food, cups, "
      + "and other tableware lie on top the table. You can still smell "
      + "the last meal that was served here."));

    add_item(({"table", "huge table"}), BSN(
        "This is a huge table, and appears to be made from solid oak. "
      + "On top of the table still lies the plates, glasses, and other "
      + "tableware from a recent meal. A dozen chairs line the sides of "
      + "the table."));

    add_item(({"plates", "glasses", "cups", "tableware"}), BSN(
        "These items lie atop the table. You notice they have been "
      + "used recently."));

    add_item(({"chandeler"}), BSN(
        "This is a very old chandeler, you figure that it is made "
      + "from crystal."));

    add_item(({"fireplace", "large fireplace"}), BSN(
        "The stone fireplace is very large, with a mantle that displays "
      + "engravings showing fine, detailed craftsmanship. It does not "
      + "appear the fireplace has been used recently."));

    add_item(({"chairs"}), BSN(
        "The chairs surround the table. You notice that they do not "
      + "match the table, and were likely only recently brought to "
      + "the manor."));

    add_engravings();

    reset_room();
}

void
reset_room()
{
    int  ic = sizeof(Corsair);

      if (!objectp(Mate))
      {
        Mate = clone_object(POROS_DIR + "npcs/mate");
        Mate->arm_me();
        Mate->move_living("down", TO);
      }

    while (ic--)
    {
      if (!objectp(Corsair[ic]))
      {
        Corsair[ic] = clone_object(POROS_DIR + "npcs/corsair");
        Corsair[ic]->arm_me();
        Corsair[ic]->add_chat("Always the same old stinking gruel to eat.");
        Corsair[ic]->add_act("emote eats some stew.");
        Corsair[ic]->add_act("emote takes a drink from his cup.");
        Corsair[ic]->move_living("down", TO);
      }
    }
}
