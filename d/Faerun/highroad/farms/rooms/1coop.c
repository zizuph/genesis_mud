/*
 * Chicken coop in a farm
 * By Finwe, November 2005
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_COOP;
inherit BASE_COMMON;


void
create_coop()
{
    iMaxEggs = 7;
    add_exit(FROOM_DIR + "1yard", "southeast");
    reset_room(); 
}

void reset_room()
{
    iEggFound = 0;
}
