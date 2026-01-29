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

string extraline = "The forest is dark and foreboding.";

void
create_forest()
{
    set_short("Deep in the" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr20", "northwest");
    add_exit(FOR_DIR + "kr21", "northeast");
    add_exit(FOR_DIR + "kr11", "southeast");
    add_exit(FOR_DIR + "kr10", "southwest");
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
