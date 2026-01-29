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

    set_extraline("The hillock sinks under your weight as you stand here " +
        "in the marsh. It seems to go on forever. The pools of water smell " +
        "and insects skirt across their surface. Insects fly around, and " +
        "buzz in your ears.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb9n1", "south", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb10n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb8n2", "west", 0, "@@move_hard@@");


}
