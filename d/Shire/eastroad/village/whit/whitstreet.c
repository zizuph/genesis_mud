inherit "/d/Shire/std/room.c";
#include "/d/Shire/common/defs.h"

void create_street() {}

void
create_shire_room()
{
    add_item(({"house","houses"}),"These houses are made of various " +
      "materials - wood, brick and stone.  They are all one story high, " +
      "because hobbits don't like heights.  Although they look occupied, "+
      "all of the doors are fastened shut from the inside, and hobbits " +
      "peer out through their windows as you walk past.\n");

    add_item(({"burrow","burrows"}),"These burrows are little more " +
      "than holes in the ground, with only a single, small window " +
      "providing light.  They are obviously owned by the poorest of " +
      "the hobbits, and look very primitive.\n");

    add_item(({"smial","smials"}),"These large smials are fancy burrows " +
      "housing the richest villagers.  They have several windows " +
      "and doors, and they look like they extend deep under the " +
      "ground.\n");

    add_item(({"lane","lanes"}),"The lanes in Whitfurrows are little " +
      "more than small, dirt roads.  On either side of the lanes are " +
      "houses and burrows, home to the hobbits of Whitfurrows.\n");

    add_item("road","This road leads from the great Eastern road to " +
      "the north, through the village of Whitfurrows.\n");
    create_street();
}
