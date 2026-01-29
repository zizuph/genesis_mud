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
    set_areaname("the rocky meadow");
    set_land("Eriador");
    set_areatype(AREATYPE_ROCKY);
    set_grass("sparse");
    set_treetype("aspen");

    set_add_rocky_plains();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("Wild flowers and grasses cover the rocky land. The " +
        "flat land is dotted with rocks and sparse vegetation.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the land.\n");

    add_exit(ER_DIR + "br3_10", "east");
    add_exit(ER_DIR + "br3_08", "west");

}

