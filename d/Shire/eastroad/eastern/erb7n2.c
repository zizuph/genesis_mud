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
    set_add_sky();

    set_extraline("The marsh stretches to the east in all directions. It " +
        "is sickly looking with sparse growth, and treacherous to travel.");

//    add_std_herbs("river");

    add_exit(ER_DIR + "erb6n1", "west", 0, "@@move_medi@@");
    add_exit(ER_DIR + "erb7n1", "south", 0, "@@move_medi@@");

}
