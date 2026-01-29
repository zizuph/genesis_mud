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
    set_extraline("The hills begin to thin here and are replaced by the forest. The trail looks bare and nothing more than a thin line in the hills. A trail leads northeast into the forest.");

    reset_faerun_room();

    add_hills1();
    add_kryptg();

    add_exit(HR_DIR + "krd03", "northwest");
    add_exit(HR_DIR + "krd01", "southeast");
    add_exit(KRYPTG_DIR + "forest/kr09", "northeast");

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


