/*
 * Hedge outside of Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
//    set_areadesc("small");
//    set_area("path");
//    set_areaname("outside the hedge");
//    set_land("Bree");

    add_my_desc("The hedge and dike turn to the northeast and " +
        "runs straight south. Some branches hang down, as if " +
        "someone tried to enter the village this way.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_dike();

    add_exit(ROAD_DIR + "nhedge06", "northeast");
    add_exit(ROAD_DIR + "nhedge04", "south");

}

