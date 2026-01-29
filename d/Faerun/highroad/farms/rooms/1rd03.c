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
    set_extraline("Trees and bushes grow thicker here. Trees grow over " +
        "the road, shading it from from the sunlight. The road widens " +
        "as it runs north with multiple ruts everywhere.");

    set_add_road();
    reset_room();

    add_exit(FROOM_DIR + "1yard", "north");
    add_exit(FROOM_DIR + "1rd02", "southwest");
}

void reset_room()
{
}
