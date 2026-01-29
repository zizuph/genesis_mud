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

string extraline = "Footprints run in every direction.";

void
create_mere()
{

    set_short("Deep in the mere");
    set_extraline(mere_descr4(extraline));
    
    add_footprints();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me13", "northeast");
    add_exit(ROOM_DIR + "me12", "northwest");
    add_exit(ROOM_DIR + "me21", "southeast");
    add_exit(ROOM_DIR + "me20", "southwest");
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
