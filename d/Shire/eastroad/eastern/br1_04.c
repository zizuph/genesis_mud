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
    set_areadesc("path");
    set_area("among sickly oaks in");
    set_areaname("the forest");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("sparse");
    set_treetype("sickly");

    set_add_marsh();
    set_add_sky();
    add_std_herbs("river");

    set_extraline("The forest is thin as it meeets the edge of a marsh. " +
        "The trees are sickly looking and look almost dead. The path " +
        "leads through the forest or straight into the marsh and is " +
        "lost among the floating hillocks.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the trees and into the marsh.\n");


    add_exit(ER_DIR + "br1_05", "east");
    add_exit(ER_DIR + "br1_03", "west");

}
