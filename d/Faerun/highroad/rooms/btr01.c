/*
 * Trail to the bandit hideout near the High Road
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
    set_short("a hidden trail in the hills");
    set_extraline("The trail wanders through the hills, past bushes and grasses. Rocks and gravel lay scattered across the hills.");

    reset_faerun_room();
    add_bandit_path("runs northeast through the bushes and southeast.");
    add_sword_mts();

    add_exit(HR_DIR + "srd13", "northeast");
    add_exit(HR_DIR + "btr02", "southeast"); 

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


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("Bandits have blocked the road, preventing travellers from " +
        "heading that way.\n");
    return 1;
} 
