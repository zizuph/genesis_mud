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

    set_extraline("Brackish water laps at your feet as you stand on a " +
        "hillock. It is dark colored with an oily film on the surface. " +
        "Insects and bugs fly around in clouds in this marsh that seems " +
        "to go on forever.");
    
    add_std_herbs("river");

    add_exit(ER_DIR + "erb11n1", "east", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb9n1", "west", 0, "@@move_hard@@");
    add_exit(ER_DIR + "erb10n2", "north", 0, "@@move_hard@@");


}

