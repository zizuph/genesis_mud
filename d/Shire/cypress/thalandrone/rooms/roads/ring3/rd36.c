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
    set_vbfc_extra(road_desc5);

    add_my_desc("The " + areadesc + " leads northeast and " +
        "southwest. To the east is a stately building, surrounded " +
        "by large trees.\n");
    add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is  surrounded by gardens and ancient trees.\n");

    add_exit(RD3_DIR + "rd37",     "northeast");
    add_exit(RD3_DIR + "rd35",     "southwest");
 
}

