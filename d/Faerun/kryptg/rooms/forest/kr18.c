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

string extraline = "To the west is a range of mountains.";

void
create_forest()
{
    set_short("The western border of" + FOR_NAME);
    set_extraline(forest_descr4(extraline));

    set_add_forest();
    set_add_mts();
 
    
    add_exit(FOR_DIR + "kr24", "northeast");
    add_exit(FOR_DIR + "kr19", "east");
    add_exit(FOR_DIR + "kr13", "southeast");
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
