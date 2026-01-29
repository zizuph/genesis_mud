/*
 * Road in Bree
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
    set_land("North Bree");

    add_my_desc("The path winds between a large dike to the north " +
        "and a very tall hedge to the south. The bushes and trees " +
        "of the hedge are tall, blocking your view of Bree. There " +
        "are some unusual claw prints in the ground, like something " +
        "has tried to rip at the hedge.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_claw_prints();

    add_exit(ROAD_DIR + "nhedge08", "east");
    add_exit(ROAD_DIR + "ngate",    "west");

}

