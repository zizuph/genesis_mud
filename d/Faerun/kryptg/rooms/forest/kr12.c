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

string extraline = "";

void
create_forest()
{
    set_short("The eastern border of" + FOR_NAME);
    set_extraline(forest_descr3(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr16", "northwest");
    add_exit(FOR_DIR + "kr17", "northeast");
    add_exit(FOR_DIR + "kr08", "south");
    add_exit(FOR_DIR + "kr07", "southwest");
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
