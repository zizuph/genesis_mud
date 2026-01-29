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

    set_extraline("Pools of brackish water surround you in the marsh. Insects " +
        "and bugs fly around you in this swamp that seems to go on forever. " +
        "Dead trees poke out of the water like dead skeletons and the " +
        "hillocks seem to shift under your feet.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb9n2", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb7n1", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb8n1", "south", 0, "@@move_hard@@");
}
