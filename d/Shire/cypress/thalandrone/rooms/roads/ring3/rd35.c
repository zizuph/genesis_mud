/*
 * Road in Third Ring of Thalandor
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "local.h"

inherit ROAD_BASE;
 
void create_road_room()
{
    set_areaname("third ring");
    set_areadesc("street");
    set_vbfc_extra(road_desc3);

    add_my_desc("The " + areadesc + " leads northeast and south " +
        "past a stately building. The building is large and " +
        "appears to be quite busy. This area is busy as elves " +
        "pass this way.\n");
    add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is  surrounded by gardens and ancient trees.\n");

    add_exit(RD3_DIR + "rd36",     "northeast");
    add_exit(RD3_DIR + "rd34",     "south");
 
}

