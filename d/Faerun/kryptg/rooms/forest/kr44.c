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

string extraline = "The trees thin and disappear to the north.";

void
create_forest()
{
    set_short("The northern border of" + FOR_NAME);
    set_extraline(forest_descr3(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr47", "northwest");
    add_exit(FOR_DIR + "kr40", "southeast");
    add_exit(FOR_DIR + "kr39", "southwest");
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
