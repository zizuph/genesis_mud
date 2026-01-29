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

#define BEACH_DIR   "/d/Faerun/red_cliffs/rooms/beach/"
string extraline = "";

void
create_mere()
{

    set_short("Deep in the mere");
    set_extraline(mere_descr5(extraline));
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me30", "northwest");
//    add_exit(BEACH_DIR + "beach01", "southeast");


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
