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
    set_vbfc_extra(road_desc1);

    add_my_desc("The "+areadesc+" leads north and south. Northeast is a " +
        "stately building. Tall ancient trees surround it as do " +
        "grand gardens. The ancient trees tower over the " +
        "building.\n");
    add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is  surrounded by gardens and ancient trees.\n");

    add_exit(RD3_DIR + "rd34",     "north");
    add_exit(RD3_DIR + "rd32",     "south");
 
}

