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

string extraline = "An ancient citadel stands north of here, hidden by the trees.";

void
create_forest()
{
    set_short("Deep in" + FOR_NAME);
    set_extraline(forest_descr2(extraline));

    set_add_forest();
    set_add_citadel();
    
    add_exit(FOR_DIR + "kr26", "northwest");
    add_exit(FOR_DIR + "kr27", "northeast");
    add_exit(FOR_DIR + "kr16", "southeast");
    add_exit(FOR_DIR + "kr15", "southwest");
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
