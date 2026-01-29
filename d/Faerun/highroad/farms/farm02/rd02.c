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
    set_short("A quiet farm road");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("Wagon ruts run down the center of the road. The road is lined with tall trees.");

    set_add_road();
    reset_room();

    add_exit(FARM2_DIR + "yard", "north");
    add_exit(FARM2_DIR + "rd01", "south");
}

void reset_room()
{
    ::reset_room();
}
