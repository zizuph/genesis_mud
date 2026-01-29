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

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("an old stone road");
    set_extraline("A sickly swamp is to the west of the road. Death and " +
        "destruction seems to rise from it. An ancient road runs alongside " +
        "it. The road is wide and well travelled as it runs across the " +
        "grassland.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_mere();
    add_std_herbs("mere");

    add_exit(HR_DIR + "srd05", "northwest");
    add_exit(HR_DIR + "srd07", "south");
    add_exit(ME_DIR + "me07", "west");

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
