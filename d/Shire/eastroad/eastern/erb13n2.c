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

    set_extraline("Bright wild flowers somehow manage to grow here in " +
        "this treacherous marsh. They grow on a hillock floating in the " +
        "water, and provide a spot of color among the dead trees and insects.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb13n3", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb12n1", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb14n1", "east", 0, "@@move_hard@@");


}

