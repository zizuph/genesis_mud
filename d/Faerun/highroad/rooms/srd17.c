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
    set_extraline("The road runs east and west into some hills. A large forest spreads to the northeast, and a thin trail run north from the road. It seems to not be maintained as a large log has fallen across the road here, making travel to the east difficult.");

    reset_faerun_room();

    add_highroad();
    add_hills();
    add_sword_mts();
    add_kryptg();
    add_std_herbs("hills");

    add_item(({"trail", "thin trail"}),
        "It is a faint track that connects with the road. The trail runs north and disappears in the hills.\n");
    add_item(({"log", "large log"}),
        "The log has fallen over the road, making travel past it impossible.\n");

    add_exit(HR_DIR + "krd01", "north");
    add_exit(HR_DIR + "srd16", "west"); 

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
