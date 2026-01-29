/*
 * Secret path for Rangers.
 * Branch 2. Runs from Weathertop to the Trollshaws
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

#define WTOP    "/d/Shire/wtop/"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("thin");
    set_area("path in");
    set_areaname("the meadow");
    set_land("Eriador");
    set_areatype(AREATYPE_ROCKY);
    set_grass("sparse");
    set_treetype("aspen");

    set_add_rocky_plains();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("The rocky land seems to go on forever and is covered " +
        "with grass and bushes. Trees grow in scattered bunches in " +
        "the distance. Bushes and shrubs grow in groups everywhere.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the land.\n");

    add_exit(ER_DIR + "br3_14", "northeast");
    add_exit(ER_DIR + "br3_12", "west");

}

