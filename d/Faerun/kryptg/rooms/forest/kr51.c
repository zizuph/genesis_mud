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

#define ORCMAKER_DIR    "/d/Faerun/orcmaker/"
#define MAX_NPCS        4

string extraline = "Caves dot the side of the mountains. A deep ravine runs northwest and southeast.";

void
create_forest()
{
    set_short("The western border of" + FOR_NAME);
    set_extraline(forest_descr3(extraline));

    set_add_forest();
    set_add_mt_caves();
    set_add_mts();
    
    add_exit(FOR_DIR + "kr53", "northeast");
    add_exit(FOR_DIR + "kr48", "south");
    add_exit(FOR_DIR + "kr49", "southeast");
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
    setuid(); 
    seteuid(getuid());

    create_orcs();
}
