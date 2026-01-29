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

string extraline = "Something has left deep scratches in the trees";

void
create_forest()
{
    set_short("Near the eastern border of" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr27", "northwest");
    add_exit(FOR_DIR + "kr28", "northeast");
    add_exit(FOR_DIR + "kr17", "southeast");
    add_exit(FOR_DIR + "kr16", "southwest");
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
