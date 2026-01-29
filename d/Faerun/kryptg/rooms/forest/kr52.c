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

string extraline = "Cutting through the forest is a deep ravine.";

void
create_forest()
{
    set_short("The northern border of" + FOR_NAME);
    set_extraline(forest_descr2(extraline));

    set_add_forest();
    set_add_mts();
    
    add_exit(FOR_DIR + "kr53", "northwest");
    add_exit(FOR_DIR + "kr50", "southeast");
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
