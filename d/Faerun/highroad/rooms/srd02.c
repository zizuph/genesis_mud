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
    set_extraline("The old stone road runs through the grassland. It runs more or less north and south past bushes and trees. To the west is a large marsh. It reeks and looks treacherous. A new path leads northeast into the bushes.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_std_herbs("mere");
    add_mere();

    add_exit(HR_DIR + "herb_clearing", "northeast");
    add_exit(HR_DIR + "srd01", "northwest");
    add_exit(HR_DIR + "srd03", "southeast");

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


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet.\n");
    return 1;
}