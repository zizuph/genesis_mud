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

    add_bree_desc("The path runs along side the hedge, which stands " +
        "as a wall protecting the village from attackers. It is " +
        "thick and impenetrable to virtually any attack.\n");

    set_add_hedge_road();
    set_add_bushes();

    add_exit(ROAD_DIR + "nhedge04", "north");
    add_exit(ROAD_DIR + "nhedge02", "south");

}

