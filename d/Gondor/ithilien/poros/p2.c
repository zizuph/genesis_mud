/*
 *   /d/Gondor/ithilien/poros/p2.c
 *
 *   This area is part of a path that leads for the Harad Road
 *   to a hidden Corsair base along the Poros in Southern Ithilien.
 *
 *   Talisan,  December 1995
 */


#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/ithilien/poros/poros_herbs.h"


void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("path");
    set_areatype(1);

    set_extraline("The path follows along the northern shore of "
        + "the river Poros. The river bank is lined with tall trees "
        + "and lush bushes, that are in stark contrast with the rest of "
        + "the surrounding region. In the distance the mountains of the Ephel Duath loom "
        + "ominously along the eastern horizon.");

    set_up_herbs( ({ ONE_OF_LIST(POROS_HERBS),
                     ONE_OF_LIST(POROS_HERBS),
                     ONE_OF_LIST(HERBS), }),
        ({"ground", "grass", "bushes"}),
      3 );

    add_exit(ITH_DIR + "poros/p1", "east", 0, 2);
    add_exit(ITH_DIR + "poros/p3", "southwest", 0, 2);

    add_item(({"path", "ground", "trail", "game trail"}), BSN(
          "The narrow walkway is little more than a game trail. It "
        + "seems to be rarely used, if at all, and is overgrown in many "
        + "areas with scrub and briar."));

    add_item(({"river", "river poros", "poros"}), BSN(
          "This is the river Poros, a tributary of the mighty Aduin. "
        + "Its source lies somewhere unknown, high in the Ephel Duath. "
        + "The river itself forms the border between Ithilien to its "
        + "north, and Harondor to the south."));

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

    add_item(({"region", "surrounding region", "plains", "ithilien",
          "southern ithilien", "countryside"}), BSN(
          "Beyond the river basin are the plains of Southern Ithilien "
        + "to the north. Scattered woodlands and an occasional hill dot "
        + "this semi-arid land that remains largely uninhabited. Low "
        + "grass and scrub brushes are the main type of vegetation that "
        + "cover the region. Somewhere far to the west lies the great "
        + "river Aduin, while in the distance to the east rises the Ephel "
        + "Duath mountain range. Across the river to the south is the "
        + "mostly barren region of Harondor."));

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
}
