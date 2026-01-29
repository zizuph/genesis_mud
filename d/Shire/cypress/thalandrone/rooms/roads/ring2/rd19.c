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
    set_areaname("second ring");
    set_areadesc("street");
    set_vbfc_extra(road_desc1);

    add_my_desc("This is an important intersection where the " +
        "West Avenue crosses the Second Ring. The West Avenue " +
        "runs east and west. The "+areadesc+" leads north and " +
        "south.\n");

    add_exit(RD2_DIR + "rd20",    "north");
    add_exit(RD2_DIR + "rd18",    "south", "@@block_road@@");
    add_exit(OTHERS_DIR + "av12", "east", "@@block_road@@");
    add_exit(OTHERS_DIR + "av11", "west");    
}

