/*
 * The Northern end of the High Road
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
    seteuid(getuid());
     
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    set_short("an old stone road");
    set_extraline("Trees and bushes have been cleared away from the road. " +
        "It runs more or less north and south through the grassland. The " +
        "road looks ancient and well travelled.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_npc("/d/Faerun/alchemy/npc/pushy", 1);

    add_exit(HR_DIR + "nrd06", "northwest");
    add_exit(HR_DIR + "nrd04", "south");
//    add_exit("/d/Faerun/leilon/rooms/lrd01", "northeast", "@@block_room@@"); 


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

    write("A Lance of Leilon steps forward and blocks you from entering the Redgate of Leilon.\n");
    return 1;
}
