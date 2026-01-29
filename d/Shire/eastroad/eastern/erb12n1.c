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

    set_extraline("The hillocks seem to float here and sink under your " +
        "weight. Dead trees stick out of the pools and stand in the " +
        "distance, while all around, the marsh extends in all directions.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb12n2", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb11n1", "west", 0, "@@move_hard@@");

}

