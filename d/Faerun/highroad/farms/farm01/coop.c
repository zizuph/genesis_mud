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
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");
    iMaxEggs = 3;
    add_exit(FARM1_DIR + "yard", "southeast");
    reset_room(); 
}

void reset_room()
{
    ::reset_room();
    iEggFound = 0;
}
