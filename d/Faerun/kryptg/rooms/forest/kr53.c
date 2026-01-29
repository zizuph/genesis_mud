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

string extraline = "Cutting through the forest is a deep ravine. Caves pepper the mountains.";

void
create_forest()
{
    set_short("The northern border of" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    set_add_mt_caves();
    set_add_mts();
    set_add_ravine();
    
    add_exit(FOR_DIR + "kr51", "southwest");
    add_exit(FOR_DIR + "kr52", "southeast");
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
