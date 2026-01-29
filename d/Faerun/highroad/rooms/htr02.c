/*
 * Trail in the hills near the High Road
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
    set_short("a rocky trail");
    set_extraline("Large boulders lay scattered across the hills. " +
        "They obscure the rocky trail, which wanders through the hills. The trail forks, heading north, southwest, and southeast.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the hills. It " +
        "is littered with rocks which hide it from casual travellers.\n");

    reset_faerun_room();

    add_grasslands();
    add_hills1();

    add_exit(HR_DIR + "htr03", "north");
    add_exit(HR_DIR + "htr01", "southwest");
    add_exit(HR_DIR + "krd04", "southeast");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}


