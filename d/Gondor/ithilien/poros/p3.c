/*
 *   /d/Gondor/ithilien/poros/p3.c
 *
 *   This area is part of a path that leads for the Harad Road
 *   to a hidden Corsair base along the Poros in Southern Ithilien.
 *
 *   Talisan,  December 1995
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/poros.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/ithilien/poros/poros_herbs.h"

//    Prototypes:
void  add_wolf();
void  reset_room();

static object wolf;

public void
add_wolf()
{
    if (!objectp(wolf))
      {
      wolf = clone_object(NPC_DIR + "wolf");
      wolf->set_restrain_path(POROS_DIR);
      wolf->move_living("down", TO);
      }
}

void
create_poros()
{

    set_extraline("The path follows along the northern shore of "
        + "the river Poros. The river bank is lined with tall trees "
        + "and lush bushes, that are in stark contrast with the rest of "
        + "the surrounding region. In the distance the mountains of the Ephel Duath loom "
        + "ominously along the eastern horizon.");

    set_up_herbs( ({ ONE_OF_LIST(POROS_HERBS),
                     ONE_OF_LIST(POROS_GOOD_HERBS),
                     ONE_OF_LIST(POROS_HERBS), }),
        ({"ground", "grass", "bushes"}),
      3 );

    add_exit(ITH_DIR + "poros/p2", "northeast", 0, 2);
    add_exit(ITH_DIR + "poros/p4", "west", 0, 2);

    add_path(0);

    add_river();

    add_item(({"bank", "banks", "river bank", "river banks", "shore",
          "northern shore", "southern shore", "river basin"}), BSN(
          "The banks of the river support a wide variety of flora, "
        + "creating a belt of greenery that marks the river's path "
        + "across the surrounding plains."));

    add_item(({"trees", "tall trees", "bushes", "lush bushes", "plants",
          "plant life", "greenery", "scrub", "briar"}), BSN(
          "Trees, bushes, as well as other plant life flourish along "
        + "the river banks. Their close proximity to the river provides "
        + "a steady supply of water, allowing for abundant growth in "
        + "this area."));

    add_region("one");

    add_item(({"harondor", "south gondor"}), BSN(
          "Across the river Poros to the south lies the lands of Harondor, "
        + "or South Gondor. Harondor is mostly an arid, barren region "
        + "that consists of badlands, and a desert interior. The coastal "
        + "strip and river basins are it's only fertile and semi-fertile "
        + "areas, providing some limited agricultural and grazing value."));

    add_item(({"ephel duath", "mountains", "mountain range"}), BSN(
          "The Ephel Duath, or Mountains of Shadow loom in the distance. "
        + "They serve as the western and southern barriers into the black "
        + "land of Mordor to the east. The range form this vantage has "
        + "a particularly sinister appearence, calling to mind evil images "
        + "of the Dark Lord himself."));

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    set_alarm(1.0, 0.0, "add_wolf");
}
