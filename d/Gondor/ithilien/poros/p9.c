/*
 *   /d/Gondor/ithilien/poros/p9.c
 *
 *   This area is part of a path that leads form the Harad Road to
 *   a hidden Corsair base along the Poros in Southern Ithilien.
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

    set_extraline("The narrow path is now just a little ways inland "
      + "from the river Poros. Through the trees, nearby to the south "
      + "can be heard the sounds of the flowing river. "
      + "To the west can be seen the gloomy form of an ancient "
      + "ruin rising out of the flat plains. Along the eastern horizon the "
      + "mountains of the Ephel Duath loom ominously in the distance.");

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass", "bushes"}));
    add_herb_file(HERB_DIR + "blueberry");
    add_herb_file(HERB_DIR + "raspberry");
    add_herb_file(HERB_DIR + "sage");
    add_herb_file(HERB_DIR + "oregano");
    add_herb_file(HERB_DIR + "coccinea");

    /*add_exit(POROS_DIR + "manor/m1", "west", 0, 2);*/
    add_exit(POROS_DIR + "manor/courtyard", "west", 0, 2);
    add_exit(ITH_DIR + "poros/p8", "northeast", 0, 2);

    add_item(({"path", "ground", "trail", "game trail"}), BSN(
        "The narrow walk way is little more than a game trail. It seems "
      + "to be rarely used, if at all, and is overgrown in many places "
      + "with scrub and briar."));

    add_item(({"river", "river poros", "poros"}), BSN(
        "The sounds of the river can be heard nearby to the south. While "
      + "at this distance only the tall trees that grow along its banks "
      + "can be seen, marking the river's course."));

    add_item(({"trees", "tall trees", "brush", "scrub brush", "plants",
        "plant life", "scrub", "briar", "bushes", "greenery",
        "small trees"}), BSN(
        "Small trees and bushes grow in this area which contrasts "
      + "the rest of the region. The plant life here "
      + "is benefiting from the nearby river, as are the tall trees, "
      + "and belt of greenery that mark the river's course as it flows "
      + "across the plains."));

    add_item(({"region", "surrounding region", "plains", "ithilien",
        "southern ithilien", "countryside"}), BSN(
        "Scatterd woodlands and an occasional hill dot the semi-arid "
      + "lands of Southern Ithilien. Low grass and scrub brushes are the "
      + "main type of vegetation that cover the region. Somewhere far to "
      + "the west lies the great river Anduin, while in the distance to "
      + "the east rises the Ephel Duath mountain range. Across the river "
      + "to the south is the mostly barren region of Harondor."));

    add_item(({"ephel duath", "mountains", "mountain range"}), BSN(
        "The Ephel Duath, or Mountains of Shadow loom in the distance. "
      + "They serve as the western and southern barriers into the black "
      + "land of Mordor to the east. The range from this vantage has a "
      + "particularly sinister appearence, calling to mind evil images "
      + "of the Dark Lord himself."));

    add_item(({"ruin", "ruins", "manor"}), BSN(
        "The ruins of what appears to be an old manor house can be "
      + "seen in the near distance to the west. The path continues to "
      + "the west entering the ruins in what appears to be a small "
      + "courtyard."));


    add_item(({"courtyard", "small courtyard"}), BSN(
        "You can see the small courtyard just to the west. It is surrounded "
      + "by a low crumbling wall, and entered trough a narrow "
      + "broken gate."));

    add_item(({"gate", "gateway", "broken gate"}), BSN(
        "At this distance its difficult to see anything significant "
      + "about the gate."));
}
