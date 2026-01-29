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
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a rocky trail");
    set_extraline("The rocky trail climbs out of the hills and up into a further up a mountain. Many rocks have rolled down from the mountain and stopped here, making travelling more difficult.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains and hills. It is littered with rocks which hide it from casual travellers.\n");

    reset_faerun_room();

    add_grasslands();
    add_hills1();

    add_exit(HR_DIR + "htr07", "northwest");
    add_exit(HR_DIR + "htr05", "southwest");

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
