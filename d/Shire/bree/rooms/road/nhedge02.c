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

    add_bree_desc("Travelling north and south, the path runs between " +
        "the hedge and the dike. Grass grows on either side of the " +
        "path which is maintained and kept clear of debris.\n");

    set_add_hedge_road();
    set_add_bushes();

    add_exit(ROAD_DIR + "nhedge03", "north");
    add_exit(ROAD_DIR + "nhedge01", "south");

}

