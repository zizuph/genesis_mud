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

string extraline = "A road connects to the forest from the southwest.";

void
create_forest()
{

    set_short("The western edge of" + FOR_NAME);
    set_extraline(forest_descr4(extraline));

    set_add_forest();
    
    add_exit(HIGHRD_DIR + "krd01", "southwest");
    add_exit(FOR_DIR + "kr09", "northwest");
    add_exit(FOR_DIR + "kr10", "northeast");
    add_exit(FOR_DIR + "kr01", "southeast");
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
