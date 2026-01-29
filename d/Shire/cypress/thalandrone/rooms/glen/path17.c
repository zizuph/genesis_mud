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
    set_vbfc_extra(road_desc4);

    add_my_desc("The "+road_type+" veers north into the forest " +
    "and south to a white building.\n");

    add_item(({"building", "white building"}),
        "The white building stands in the distance, south of " +
        "here. It lies hidden in the trees and looks impressive.\n");

    add_exit(GLEN_DIR + "path16", "north");
    add_exit(GLEN_DIR + "front", "south");
}
