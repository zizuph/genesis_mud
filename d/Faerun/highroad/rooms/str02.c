/*
 * Trail in the Grasslands near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

string extra_line = "";

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("A game trail");
    set_extraline("The grass comes up to your waist and bends in the " +
        "breeze. It covers the land and hides a game trail that runs " +
        "through it. Small animals dart around in the grass. A bird " +
        "occasionally flies out of the grass.");

    reset_faerun_room();

    add_grasslands();
    add_std_herbs("meadow");

    add_item(({"trail"}),
        "It is a small furrow of trampled grass that runs east, west, and southwest " +
        "through the grassland.\n");


    add_exit(HR_DIR + "srd01", "east");
    add_exit(HR_DIR + "str01", "west");
    add_exit(HR_DIR + "beach02", "southwest");
    add_exit(HR_DIR + "str02s", "south");


}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}


