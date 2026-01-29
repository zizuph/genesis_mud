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

    set_extraline("The area seems drier here, as if the hillock is on " +
        "higher ground. The marsh spreads north and east before you, but " +
        "to the west and south, the Great East road runs alongside the marsh.");

    add_std_herbs("river");

    add_exit(ER_DIR + "erb9n1", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb8", "south", 0, "@@move_med@@");
    add_exit(ER_DIR + "erb8n2", "north", 0, "@@move_med@@");
}
