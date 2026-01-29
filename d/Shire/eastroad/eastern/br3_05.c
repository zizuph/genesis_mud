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
    set_areadesc("rocky");
    set_area("path near");
    set_areaname("the rolling hills");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("sparse");
    set_treetype("aspen");

//    set_add_weather_hills();
    set_add_east_whills();
    set_add_rocky_plains();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("It veers west and southeast across the land. The " +
        "rocky land seems to go on forever and is covered with grass " +
        "and bushes. Trees grow in scattered bunches in the distance.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the land.\n");

    add_exit(ER_DIR + "br3_06", "southeast");
    add_exit(ER_DIR + "br3_04", "west");

}

