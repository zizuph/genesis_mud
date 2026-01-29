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

string extraline = "The trail swings past trees and bushes.";

void
create_forest()
{
    set_short("Near the western border of" + FOR_NAME);
    set_extraline(forest_descr5(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr24", "north");
    add_exit(FOR_DIR + "kr13", "south");
    add_exit(FOR_DIR + "kr25", "northeast");
    add_exit(FOR_DIR + "kr14", "southeast");
    add_exit(FOR_DIR + "kr18", "west");
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
