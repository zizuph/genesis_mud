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

    add_my_desc("You stand outside the village of Bree, between " +
        "a hedge and dike surround Bree. The hedge, which " +
        "is closest to the village, is a wall of tall trees, while " +
        "the dike is a secondary barrier that surrounds it all.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_dike();

    add_exit(ROAD_DIR + "nhedge05", "north");
    add_exit(ROAD_DIR + "nhedge03", "south");

}

