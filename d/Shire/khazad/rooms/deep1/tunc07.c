/*
 * Great Arch in Moria from West-gate
 * By Finwe, February 2003
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit BASE_ROOM;

void
create_mine_room()
{
    LIGHTS_OFF;
    set_areadesc("dark tunnel");
    set_area("in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    
    add_my_desc("The tunnel is wide and long. It was carved from the " +
        "mountain, and feels dead now. The walls are tall, reaching " +
        "up into cold darkness. Cobwebs are draped across the surface " +
        "and some skeletons alongside the walls.\n");

    set_add_walls("");
    set_add_ceiling("");
    set_add_floor("");
    set_add_west_gate_stairs("");

    NORTH(DEEP1_DIR + "archc08");
    SOUTH(DEEP1_DIR + "archway");

}
