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
    set_extraline("The road meaders past a large swamp to the west. It " +
        "looks well travelled and is old. The cobbles are smooth from " +
        "many years of traffic.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_mere();
    add_std_herbs("mere");

    add_exit(HR_DIR + "srd04", "west");
    add_exit(HR_DIR + "srd06", "southeast");
    add_exit(ME_DIR + "me07", "south");
    add_exit(FARM1_DIR + "rd01", "northeast");

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
