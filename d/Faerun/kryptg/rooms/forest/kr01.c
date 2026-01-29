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

string extraline = "The trees thin to the south.";

void
create_forest()
{

    set_short("The southern border of" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr05", "northwest");
    add_exit(FOR_DIR + "kr06", "northeast");
    add_exit(FOR_DIR + "kr02", "east");
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
