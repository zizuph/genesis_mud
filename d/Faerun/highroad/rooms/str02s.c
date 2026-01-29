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

//inherit HIGH_RD_DIR + "std/base_road.c";
inherit BASE_ROAD;
inherit "/d/Faerun/herbs/herbsearch.c";

string extra_line = "";

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");

    set_short("An open field");
    set_extraline("The field is off the game trail and has been trampled flat. Small animals dart around in and out of the grass. Clouds float overhead.");

    reset_faerun_room();

    add_grasslands();
    add_std_herbs("meadow");

    add_item(({"trail"}),
        "A trail leads north away from the field.\n");


    add_exit(HR_DIR + "str02", "north");
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


