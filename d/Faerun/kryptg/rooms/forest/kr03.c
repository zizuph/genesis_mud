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

string extraline = "Bushes grow over the trail, obscuring it from view.";

void
create_forest()
{

    set_short("The southern border of" + FOR_NAME);
    set_extraline(forest_descr5(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr02", "west");
    add_exit(FOR_DIR + "kr06", "northwest");
    add_exit(FOR_DIR + "kr07", "northeast");
    add_exit(FOR_DIR + "kr04", "east");
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
