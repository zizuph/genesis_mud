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

string extraline = "";

void
create_mere()
{

    set_short("Somewhere in the mere");
    set_extraline(mere_descr1(extraline));
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me06", "northeast");
    add_exit(ROOM_DIR + "me05", "northwest");
    add_exit(ROOM_DIR + "me14", "southeast");
    add_exit(ROOM_DIR + "me13", "southwest");
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
