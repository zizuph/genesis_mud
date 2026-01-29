/*
 *   /d/Gondor/ithilien/poros/manor/foyer.c
 *
 *   The entryway into the manor that serves as a base for corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

void
create_manor()
{
    set_area("foyer");
    set_extraline("The entry hall into the manor is in relatively good "
      + "condition compared to most parts of the building. A large fireplace "
      + "dominates the northwest corner of the room, while to the north "
      + "and west hallways continue further into the manor. To the southeast "
      + "lies a broken door, beyond which a flight of stairs leads down into "
      + "a small courtyard.");

    add_exit(POROS_DIR + "manor/westhall1", "west", 0, 1);
    add_exit(POROS_DIR + "manor/southhall", "north", 0, 1);
    add_exit(POROS_DIR + "manor/courtyard", "southeast", 0, 1);

    add_item(({"fireplace", "large fireplace"}), BSN(
        "The stone fireplace is very large, with a mantle that displays "
      + "engravings that show fine, detailed craftsmanship. You notice that "
      + "it seems to have been ages since the fireplace was last used. Many "
      + "cobwebs hang within the fireplace, attesting to this. However you "
      + "find the fireplace strangely warm to the touch..."));

    add_item(({"stairs"}), BSN(
        "The flight of stone stairs leads from the foyer down into the "
      + "courtyard. You can see the steps are overgrown with weeds, and "
      + "crumbling in many areas."));

    add_item(({"courtyard"}), BSN(
        "You can catch only a glimpse of the courtyard through the "
      + "doorway to the southeast."));

    add_item(({"foyer", "floor", "ground", "entry hall"}), BSN(
        "You notice the foyer looks as if it has been lying undisturbed "
      + "for centuries. Broken furniture, and a rotting carpet lie on the "
      + "floor here, giving the room a rather musty smell."));

    add_door();
    add_furniture();
    add_carpet();
    add_engravings();
    add_house();
}
