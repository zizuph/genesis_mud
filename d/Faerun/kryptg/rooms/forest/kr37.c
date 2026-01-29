/*
 * Path in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_FOREST;

string extraline = "The trail winds past bushes and trees as it runs deeper into the forest.";

void
create_forest()
{
    set_short("Near the western border of" + FOR_NAME);
    set_extraline(forest_descr2(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr41", "northwest");
    add_exit(FOR_DIR + "kr42", "northeast");
    add_exit(FOR_DIR + "kr32", "southeast");
    add_exit(FOR_DIR + "kr31", "southwest");
    reset_faerun_room();
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
