/*   /d/Gondor/ithilien/poros/manor/southhall.c
 *
 *   A hallway in the manor thats a hidden corsair base.
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
    set_extraline("A collapsed flight of stairs lies in ruins along the "
      + "western wall, while the hallway continues to the north and south.");

    add_exit(POROS_DIR + "manor/northhall", "north", 0, 1);
    add_exit(POROS_DIR + "manor/foyer", "south", 0, 1);

    add_item(({"stairs", "steps"}), BSN(
        "The stairs are completely collapsed and filled with rubble. You "
      + "suspect the manor's roof has fallen totally in this section "
      + "of the building."));

    add_hallway();
    add_rubble();
    add_house();
}
