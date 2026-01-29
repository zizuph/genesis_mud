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
    set_extraline("The trail suddenly veers to the east near the top " +
        "of the mountain. Large boulders are scattered around the area. " +
        "From up here, you can see down to the grassland to the west " +
        "and north. The trail dips down to the east and disappears.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It " +
        "is littered with rocks which hide it from casual travellers.\n");

    reset_faerun_room();

    add_grasslands();
    add_sword_mts1();

    add_exit(HR_DIR + "htr08", "east");
    add_exit(HR_DIR + "htr06", "southeast");

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
