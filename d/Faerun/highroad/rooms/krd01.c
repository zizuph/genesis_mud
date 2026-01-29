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
    set_extraline("The trail passes by a forest, which replaces the hills. The forest  spreads to the north and seems to go on forever. It branches to the northeast and disappears into the trees.");

    reset_faerun_room();

    add_hills1();
    add_kryptg();

    add_exit(HR_DIR + "srd17", "south");
    add_exit(HR_DIR + "krd02", "northwest");
    add_exit(KRYPTG_DIR + "forest/kr05", "northeast");

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


