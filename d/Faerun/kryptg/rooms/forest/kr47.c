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

string extraline = "To the south, a deep ravines runs northwest and southeast.";

void
create_forest()
{
    set_short("The northern border of" + FOR_NAME);
    set_extraline(forest_descr5(extraline));

    set_add_forest();
    set_add_ravine();
    
    add_exit(FOR_DIR + "kr50", "northwest");
    add_exit(FOR_DIR + "kr44", "southeast");
    add_exit(FOR_DIR + "kr43", "southwest");
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
