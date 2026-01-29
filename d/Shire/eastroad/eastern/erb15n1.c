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

    set_extraline("A rank stench fills the air rising up from the waters " +
        "of the marsh. Great clouds of insects buzz around, and skitter " +
        "across the hillocks. Water from the brackish pools lap against " +
        "the hillocks. The Great East road can be seen to the east.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb14n1", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb16", "east", 0, "@@move_med@@");
    add_exit(ER_DIR + "erb15n2", "north", 0, "@@move_hard@@");

}

