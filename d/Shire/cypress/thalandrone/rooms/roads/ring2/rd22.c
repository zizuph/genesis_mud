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
    set_vbfc_extra(road_desc5);

    add_my_desc("The "+areadesc+" runs northeast and southwest. " +
        "To the west is a stately building and east is an " +
        "ornate building.\n");
    add_item("ornate building",
        "The ornate building is long with several wings " +
        "branching off of it. It has a flat roof and is nearly " +
        "hidden in the trees.\n");
   add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is surrounded by gardens and nearly hidden by " +
        "ancient trees.\n");

    add_exit(RD2_DIR + "rd23",    "northeast");
    add_exit(RD2_DIR + "rd21",    "southwest");
}

