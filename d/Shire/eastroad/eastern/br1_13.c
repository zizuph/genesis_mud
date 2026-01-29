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

    set_add_weather_hills();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("The land is rocky and surrounded by rolling hills. " +
        "They stretch to the east and are covered with small bushes and " +
        "grasses. To the west, the marsh can be seen in the distance. " +
        "A path runs east through the hills and west.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the hills and into the marsh.\n");

    add_exit(ER_DIR + "br1_14", "east");
    add_exit(ER_DIR + "br1_12", "west");

}
