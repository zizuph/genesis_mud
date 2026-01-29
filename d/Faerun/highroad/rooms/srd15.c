/*
 * The High Road
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
    set_extraline("The road runs through the hills. They are brown and rocky looking, and covered with grass. They hide from view anything coming along the road.");

    reset_faerun_room();

    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("hills");

    add_exit(HR_DIR + "srd14", "northwest");
    add_exit(HR_DIR + "srd16", "east"); 

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

    write("Bandits have blocked the road, preventing travellers from " +
        "heading that way.\n");
    return 1;
} 
