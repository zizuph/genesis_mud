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
    set_areadesc("dark area");
    set_area("bogs in");
    set_areaname("the Midgewater Marshes");
    set_land("Eriador");
    set_areatype(AREATYPE_MARSH);
    set_grass("sparse gray");
    set_treetype("dead");

    set_add_marsh();
    set_add_sky();
    add_std_herbs("river");

    set_extraline("The marsh spreads out to the north, west, and south " +
        "and seems to go on forever. Dead trees, the remnants of a " +
        "great forest, stand in the water. Bugs skitter across the " +
        "hillocks and water laps at your feet.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the marsh and out into the land.\n");

    add_exit(ER_DIR + "br1_12", "northeast");
    add_exit(ER_DIR + "br1_10", "southwest");

}
