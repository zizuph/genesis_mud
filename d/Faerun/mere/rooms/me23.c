/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;

string extraline = "Claw marks are visible in the grass";

void
create_mere()
{

    set_short("Somewhere in the mere");
    set_extraline(mere_descr4(extraline));
    
    add_std_herbs("mere");

    reset_faerun_room();
    add_claws_ground();
    
    add_exit(ROOM_DIR + "me19", "northeast");
    add_exit(ROOM_DIR + "me18", "northwest");
    add_exit(ROOM_DIR + "me28", "southeast");
    add_exit(ROOM_DIR + "me27", "southwest");
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
