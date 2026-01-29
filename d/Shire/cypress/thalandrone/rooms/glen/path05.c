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

    add_my_desc("The "+road_type+" runs along the top of a " +
    "small rise in the forest.\n");

    add_item(({"small rise"}),
        "The hill is nothing more than a small hump in the road. " +
        "It is clean with some plants growing on it.\n");

    add_exit(GLEN_DIR + "path04", "north");
    add_exit(GLEN_DIR + "path06", "southwest");
}
