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
    set_extraline("The road passes through hills along the western " +
        "side of some tall mountains. The road looks dangerous with " +
        "many places where bandits hide. To the southwest, you see " +
        "a narrow, trodden road ascending up to a steep cliff, atop " +
        "which sits a stone fortress.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("hills");

    add_exit(HR_DIR + "srd11", "northwest");
    add_exit(HR_DIR + "srd13", "southeast");
//   add_exit("/d/Faerun/thornhold/rooms/thornhold_road_01", "southwest"); //

// When Thornhold is complete, remove no_exit_msg and connect this   //
// room with above commented-out exit. //

    set_no_exit_msg(({"southwest"}),
    "The road southwest is blocked by jagged rocks and " +
    "scattered scree from a recent rockslide. It will " +
    "likely be cleared in the coming months.\n");

    add_item(({ "fortress", "cliff", "fortress", "Thornhold", "thornhold" }),
                "In the distance you see the gray stone fortress of " +
                "Thornhold perched above the Mere of Dead Men atop a " +
                "seaside cliff.\n");

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


