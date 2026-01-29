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

    set_extraline("The dark water seems to stretch forever, in this marsh. " +
    "There is nothing that looks alive except for the insects that buzz " +
    "around you and scurry across the hillocks.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb12n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb11n2", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n3", "east", 0, "@@move_hard@@");

}

