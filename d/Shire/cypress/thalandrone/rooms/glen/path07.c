/*
 * Forest path leading to Wild Elves Guild
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "/d/Shire/cypress/thalandrone/local.h"

//inherit "/d/Shire/cypress/thalandrone/base_road.c";
inherit FOREST_BASE;

//string road_type = "path";

void
create_forest_room()
{
    set_vbfc_extra(road_desc2);

    add_my_desc("A small hill lies north in the distance.\n");

    add_item(({"small rise"}),
        "The hill is a small hump in the road.\n");

    add_exit(GLEN_DIR + "path06", "east");
    add_exit(GLEN_DIR + "path08", "southwest");
}
