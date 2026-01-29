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
    set_extraline("The trail runs through the hills. It's rocky and passes by a large forest. The forest stretches to the northeast, and looks dangerous.");

    reset_faerun_room();

    add_hills1();
    add_kryptg();

    add_exit(HR_DIR + "htr02", "northwest");
    add_exit(HR_DIR + "krd03", "southeast");

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


