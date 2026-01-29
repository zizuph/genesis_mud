/*
 * Road leading to farm
 * By Finwe, August 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARM;

void
create_farm_room()
{
    set_short("A winding farm road");
    set_extraline("The road crosses through meadows, running northeast and southwest. It looks well used with ruts running down the center. Bushes and trees grow on either side of it.");

    set_add_road();
    reset_room();

    add_exit(FROOM_DIR + "1rd02", "north");
    add_exit(HR_DIR + "srd05", "southwest");
}

void reset_room()
{
}
