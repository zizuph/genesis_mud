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
    set_areadesc("junction");
    set_area("in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    
    add_my_desc("Dark tunnels meet here, arriving from many directions " +
        "through several archways. The air from some of the tunnels " +
        "smells putrid and evil while fresh air blows through others. " +
        "The walls are cloaked in darkness and shadows with cobwebs " +
        "hanging from torch stands.\n");

    set_add_arches("They lead northeast and southwest, with another at " +
        "the south end of the tunnel.");

    set_add_walls("");
    set_add_ceiling("");
    set_add_floor("");

    NORTHEAST(DEEP1_DIR + "archd09");
    NORTHWEST(DEEP1_DIR + "archb09");
    SOUTH(DEEP1_DIR + "tunc07");

}
