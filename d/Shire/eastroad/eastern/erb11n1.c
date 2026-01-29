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

    set_extraline("Swarms of insects rise up from the swamp. They buzz " +
        "around you, then settle down on the hillocks and dead trees. To " +
        "the south, the Great East road wanders through the trees.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb11n2", "north", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb11", "south", 0, "@@move_med@@");
    add_exit(ER_DIR + "erb10n1", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb12n1", "east", 0, "@@move_hard@@");


}

