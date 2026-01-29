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
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("A winding farm road");
    set_extraline("Bushes and trees grow in scattered groups. The road " +
        "winds past the trees and bushes. Wagon ruts run down the middle " +
        "of the road.");

    set_add_road();
    reset_room();

    add_exit(FARM1_DIR + "rd03", "northeast");
    add_exit(FARM1_DIR + "rd01", "south");
}

void reset_room()
{
    ::reset_room();
}
