#pragma save_binary
#pragma strict_types

#include "local.h"
#include "/d/Shire/common/herbs/herb_list.h"
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

    set_extraline("This is the edge of the marsh. It stretches to the " +
        "north, south, and west. The hillocks seem to float in the water, " +
        "and are covered with dead plants. Trees once grew heavily here, " +
        "but are long dead.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb14n2", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb15n2", "southeast", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb13n3", "southwest", 0, "@@move_hard@@");

}

