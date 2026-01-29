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

    add_my_desc("The "+areadesc+" runs east and southwest. The " +
        "Northwest Avenue crosses the "+areadesc+" as it runs " +
        "in a southeast direction. To the west is a stately " +
        "building and south is an ornate building.\n");
    add_item("ornate building",
        "The ornate building is long with several wings " +
        "branching off of it. It has a flat roof with several " +
        "wings. The building is nearly hidden by the trees.\n");
   add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is surrounded by gardens and nearly hidden by " +
        "ancient trees.\n");


    add_exit(RD2_DIR + "rd24",    "east", "@@block_rd@@");
    add_exit(OTHERS_DIR + "av02", "northwest");
    add_exit(OTHERS_DIR + "av03", "southeast", "@@block_rd@@");
    add_exit(RD2_DIR + "rd22",    "southwest");


}

