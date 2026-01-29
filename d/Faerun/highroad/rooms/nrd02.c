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
    set_extraline("The road runs north and south, cutting through " +
        "grasslands. The ancient road is well travelled and covered with " +
        "large cobblestones. It looks well travelled and has been in " +
        "use for countless years.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit(HR_DIR + "nrd03", "northwest");
    add_exit(HR_DIR + "nrd01", "southeast");
//    add_exit("/d/Faerun/leilon/rooms/wgate", "northeast", "@@block_room@@"); 

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

    write("A Lance of Leilon steps forward and blocks you from entering the Seagate of Leilon.\n");
    return 1;
}