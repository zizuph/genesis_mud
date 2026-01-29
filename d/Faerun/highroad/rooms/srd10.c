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

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("an old stone road");
    set_extraline("Hills surround the road. They rise above you, blocking " +
        "your view on either side. South are some tall mountains. They " +
        "look rough and irregular.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("meadow");

    add_exit(HR_DIR + "srd09", "northwest");
    add_exit(HR_DIR + "srd11", "southeast");

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


