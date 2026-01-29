/*
 * The High Road
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
    set_extraline("The trail meanders from the southwest and to the east, " +
        "across the grasslands. The land is open and high. Birds are " +
        "singing and small animals play in the grass.");

    reset_faerun_room();

    add_grasslands();
    add_std_herbs("meadow");

    add_item(({"trail"}),
        "It is a small furrow of trampled grass that runs through the grassland.\n");


    add_exit(HR_DIR + "str02", "east");
    add_exit(HR_DIR + "beach03", "west");
    add_exit(HR_DIR + "beach02", "south");
    add_exit(HR_DIR + "beach01", "southwest");

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
