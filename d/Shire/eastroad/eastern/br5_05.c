/*
 * Secret path for Rangers.
 * Branch 2. Runs from Weathertop to the Trollshaws
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("thin");
    set_area("path near");
    set_areaname("the trollshaws");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_treetype("conifers");

    set_add_trollshaws();
    set_add_sky();
    add_std_herbs("hills");

    set_extraline("The bushes grow thick here making it difficult to " +
        "travel. Several paths lead off in different directions, but " +
        "there are two that lead east and southwest. Paw prints are " +
        "visible in the ground.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the area.\n");

    add_exit(ER_DIR + "br5_06", "east");
    add_exit(ER_DIR + "br5_04", "southwest");


}

