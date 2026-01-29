/*
 * Road in Bree
 * By Finwe, April 2002
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("deserted");
    set_area("road");
    set_areaname("outside");
    set_land("north Bree");

    add_bree_desc("The road runs east into the village of Bree. The " +
        "North Gate stands to the east. A large " +
        "hedge is visible in the distance, surrounded by a deep " +
        "dike. Paw prints are visible in the ground.\n");

    set_add_claw_prints();
    set_add_outside_hedge();
    set_add_dike();

    add_exit(ROAD_DIR + "ngate",  "east");
    add_exit(ROAD_DIR + "road02", "southwest");
}
