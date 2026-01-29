/*
 * The High Road
 * -- Finwe, July 2006
 * ------------------------------------------------------------------
 * 2022/02/15 Brine Open the south highroad link to mortals
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
    set_extraline("The hills are brown looking as the road travels east and west through them. Their rocky sides are covered with grass and they look wind-blown.");

    reset_faerun_room();

    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("hills");

    add_exit(HR_DIR + "srd17", "east");
    add_exit(HR_DIR + "srd15", "west");
    add_exit(SOUTH_HIGHROAD_LINK, "south");

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
