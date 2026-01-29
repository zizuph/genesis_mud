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

string extraline = "To the south is a deep ravine.";

void
create_forest()
{
    set_short("The northern border of" + FOR_NAME);
    set_extraline(forest_descr1(extraline));

    set_add_forest();
    
    add_exit(FOR_DIR + "kr52", "northwest");
    add_exit(FOR_DIR + "kr47", "southeast");
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
