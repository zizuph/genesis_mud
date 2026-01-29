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

    set_extraline("Dead trees stand scattered around the marsh. Many of " +
        "them are flooded by the brackish water or surrounded by the " +
        "hillocks that float nearby. Wild flowers grow on some of the " +
        "hillocks, providing a little color in the drab marsh.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb14n3", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb15n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n3", "west", 0, "@@move_hard@@");

}

