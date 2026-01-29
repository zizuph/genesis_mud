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
    set_extraline("The trail is thin and winds through the hills, and " +
        "meanders past boulders. Large rocks have fallen down from the " +
        "mountain and lay scattered on the trail.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It " +
        "is littered with rocks which hide it from casual travellers.\n");

    reset_faerun_room();

    add_grasslands();
    add_hills1();

    add_exit(HR_DIR + "htr02", "northeast");
    add_exit(HR_DIR + "srd11", "southwest");

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


