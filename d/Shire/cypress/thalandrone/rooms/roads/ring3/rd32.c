/*
 * Road in Third Ring of Thalandor
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "local.h"

//inherit "/d/Shire/cypress/thalandrone/base_road.c";
inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areaname("third ring");
    set_areadesc("street");
    set_vbfc_extra(road_desc4);

    add_my_desc("The "+areadesc+" leads north and south. Tall, ancient " +
        "trees line the road, creating a canopy that hides the " +
        "city.\n");

    add_exit(RD3_DIR + "rd33",     "north");
    add_exit(RD3_DIR + "rd31",     "south");
 
}

