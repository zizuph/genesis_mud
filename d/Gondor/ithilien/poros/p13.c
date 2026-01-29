/*
 *   /d/Gondor/ithilien/poros/p13.c
 *
 *   This area is part of the path that is a decoy meant to trow off
 *   those looking for the hidden Corsair base along the Poros.
 *
 *   Talisan,  December 1995
 *
 *   Toby fixed typo @21 feb 2007
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"

void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("path");
    set_areatype(1);

    set_extraline("The path here is now inland from the river Poros. "
      + "To the north the path loses definition, becoming overgrown "
      + "with grass and scrub brush, blending into the surrounding region. "
      + "Along the eastern horizon the mountains of the Ephel Duath loom ominously "
      + "in the distance.");

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass", "bushes"}));
    add_herb_file(HERB_DIR + "blackberry");
    add_herb_file(HERB_DIR + "mint");
    add_herb_file(HERB_DIR + "rosemary");
    add_herb_file(HERB_DIR + "sage");
    add_herb_file(HERB_DIR + "attanar");

    add_exit(ITH_DIR + "poros/p12", "south", 0, 2);

    add_item(({"path", "ground", "trail", "game trail"}), BSN(
        "The narrow walk way is little more than a game trail. It seems "
      + "to be rarely used, if at all, and is overgrown in many places "
      + "with scrub and briar."));

    add_item(({"trees", "bushes", "brush", "scrub brush", "scrub",
        "briar", "grass", "vegetation"}), BSN(
        "Low grass and scrub brushes are the main type of vegetation "
      + "that grows in the area. While traveling a few small trees can "
      + "be seen occasionally out across the countryside."));

    add_item(({"region", "surrounding region", "plains", "ithilien",
        "southern ithilien", "countryside", "surrounding countryside"}), BSN(
        "Scattered woodlands and an occasional hill dot this semi-arid "
      + "land that remains largely uninhabited. Low grass and scrub "
      + "brushes are the main type of vegetation covering the region. "
      + "The great river Anduin lies somewhere west of here, while the "
      + "tall mountain peaks of Ephel Duath rise on the eastern horizon. "
      + "Across the river Poros, which flows somewhere south of here, is "
      + "the mostly barren region of Harondor."));

    add_item(({"ephel duath", "mountains", "mountain range"}), BSN(
        "The Ephel Duath, or Mountains of Shadow loom in the distance. "
      + "They serve as the western and southern barriers into the black "
      + "land of Mordor to the east. The range from this vantage has a "
      + "particularly sinister appearance, calling to mind evil images "
      + "of the Dark Lord himself."));
}
