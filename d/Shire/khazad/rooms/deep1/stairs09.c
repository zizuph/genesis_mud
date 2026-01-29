/*
 * Stairs in Moria from West-gate
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
    set_area("in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    set_areadesc("long staircase");
    
    add_my_desc("The stairs lead up into the mountain and blackness, " +
        "and down into darkness. They were obviously carved by dwarves " +
        "who once lived here, and they seem to run up and down forever.\n");

    set_add_walls("");
    set_add_ceiling("");
    set_add_floor("");
    set_add_west_gate_stairs("");

    UP(DEEP1_DIR + "stairs10");
    DOWN(DEEP1_DIR + "stairs08");

}
