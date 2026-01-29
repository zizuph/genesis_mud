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
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    set_short("an old stone road");
    set_extraline("Trees and bushes have been cleared away from the road. " +
        "It runs roughly north and south through grasslands. The road " +
        "looks ancient and well travelled.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit(HR_DIR + "nrd02", "northwest");
    add_exit(HR_DIR + "srd01", "southeast");
//    add_exit(HR_DIR + "nrd01a", "east", "@@block_room@@"); 


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

    write("A Lance of Leilon steps forward and blocks you from entering the Cryptgate of Leilon.\n");
    return 1;
}
