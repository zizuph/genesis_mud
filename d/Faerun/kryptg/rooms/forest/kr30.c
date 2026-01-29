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

string extraline = "Tall mountains rise from the west.";

void
create_forest()
{
    set_short("The western border of" + FOR_NAME);
    set_extraline(forest_descr2(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr36", "northeast");
    add_exit(FOR_DIR + "kr25", "southeast");
    add_exit(FOR_DIR + "kr24", "south");
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
