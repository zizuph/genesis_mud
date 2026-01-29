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

string extraline = "Caves dot the upper reaches of the mountains to the west.";

void
create_forest()
{
    set_short("The western border of" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    set_add_mt_caves();
    set_add_mts();
    
    add_exit(FOR_DIR + "kr48", "north");
    add_exit(FOR_DIR + "kr49", "northeast");
    add_exit(FOR_DIR + "kr42", "southeast");
    add_exit(FOR_DIR + "kr41", "southwest");
//    add_exit(FOR_DIR + "kr", "west");
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
