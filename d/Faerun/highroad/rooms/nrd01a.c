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
    set_short("a wide road");
    set_extraline("It is well travelled and connects the Highroad with the city to the east. The road is well maintained and broad.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();

    add_exit("/d/Faerun/leilon/rooms/sgate", "east");
    add_exit(HR_DIR + "nrd01", "west"); 
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

    write("A Lance of Leilon steps forward and blocks you from entering the Cryptgate of Leilon.\n");
    return 1;
}
