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

string extraline = "A road angles around the mere.";

void
create_mere()
{

    set_short("Near the edge of the mere");
    set_extraline(mere_descr2(extraline));
    
    add_road();
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "me19", "northwest");
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
