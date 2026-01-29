/*
 * Secret path for Rangers.
 * Branch 1. Runs from Bree to Weathertop
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("rocky");
    set_area("path in");
    set_areaname("the rolling hills");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("sparse gray");
    set_treetype("dead");

    set_add_marsh();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("The marsh spreads out to the north, west, and south " +
        "and seems to go on forever. Dead trees, the remnants of a " +
        "great forest, stand in the water. Bugs skitter across the " +
        "hillocks and water laps at your feet.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the marsh and out into the land.\n");

    add_exit(ER_DIR + "br1_13", "east");
    add_exit(ER_DIR + "br1_11", "southwest");

}
