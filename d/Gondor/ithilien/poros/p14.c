/*
 *   /d/Gondor/ithilien/poros/p14.c
 *
 *   This area is part of the path that is a decoy meant to trow off
 *   those looking for the hidden Corsair base along the Poros.
 *
 *   Talisan,  December 1995
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

    set_extraline("The path here is now inland from the river Poros, "
      + "going through an area of low grass and scrub brushes. "
      + "To the west a small hill rises above the plains, and "
      + "along the eastern horizon the mountains of the Ephel Duath loom ominously "
      + "in the distance.");

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass", "bushes"}));
    add_herb_file(HERB_DIR + "blueberry");
    add_herb_file(HERB_DIR + "blackberry");
    add_herb_file(HERB_DIR + "raspberry");
    add_herb_file(HERB_DIR + "braspberry");
    add_herb_file(HERB_DIR + "sage");

    add_exit(ITH_DIR + "poros/p15", "west", 0, 4);
    add_exit(ITH_DIR + "poros/p11", "southeast", 0, 2);

    add_item(({"path", "ground", "trail", "game trail"}), BSN(
        "The narrow walk way is little more than a game trail. It seems "
      + "to be rarely used, if at all, and is overgrown in many places "
      + "with scrub and briar."));

    add_item(({"trees", "bushes", "brush", "scrub brush", "scrub",
        "briar", "grass", "vegetation"}), BSN(
        "Low grass and scrub brushes are the main type of vegetation "
      + "that grows in the area. While traveling a few small trees can "
      + "be seen occasionaly out across the countryside."));

    add_item(({"region", "surrounding region", "plains", "ithilien",
        "southern ithilien", "countryside", "surrounding countryside"}), BSN(
        "Scattered woodlands and an occasional hill dot this semi-arid "
      + "land that remains largely uninhabited. Low grass and scrub "
      + "brushes are the main type of vegetation that cover the region. "
      + "Somewhere far to the west lies the great river Anduin, while "
      + "in the distance to the east rises the Ephel Duath mountain range. "
      + "Across the river poros somewhere to the south, is the mostly "
      + "barren region of Harondor."));

    add_item(({"ephel duath", "mountains", "mountain range"}), BSN(
        "The Ephel Duath, or Mountains of Shadow loom in the distance. "
      + "They serve as the western and southern barriers into the black "
      + "land of Mordor to the east. The range from this vantage has a "
      + "particularly sinister appearance, calling to mind evil images "
      + "of the Dark Lord himself."));

    add_item(({"hill", "small hill", "rise"}), BSN(
        "The hill rises above the surrounding plains, marking a sharp "
      + "contrast with the surrounding region. The hill is small by "
      + "most standards, but will likely offer a commanding view of "
      + "the local countryside."));
}
