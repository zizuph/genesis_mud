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
    set_vbfc_extra(road_desc1);

    add_my_desc("The path runs southwest deeper into the " +
        "forest and northeast towards a forest glen.\n");

    add_exit(GLEN_DIR + "glen",   "northeast");
    add_exit(GLEN_DIR + "path02", "southwest");
}
