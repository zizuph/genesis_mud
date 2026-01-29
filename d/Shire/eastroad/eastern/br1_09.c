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

    set_extraline("There is nothing that looks alive in the marsh. Dead " +
        "trees rise out of the fetid water. Insects buzz around the " +
        "marsh that seems to go on forever.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the marsh.\n");


    add_exit(ER_DIR + "br1_10", "east");
    add_exit(ER_DIR + "br1_08", "northwest");

}
