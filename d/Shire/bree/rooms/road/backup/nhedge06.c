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

    add_my_desc("You stand on a path that runs outside the village, " +
        "between a dike to your west and a tall hedge to your east. " +
        "They both follow the fringes of Bree, offering some " +
        "protection from invaders and barbarians.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_dike();

    add_exit(ROAD_DIR + "ngate",    "north");
    add_exit(ROAD_DIR + "nhedge05", "southwest");

}

