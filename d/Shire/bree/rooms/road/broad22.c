/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("deserted");
    set_area("quiet");
    set_areaname("road");
    set_land("Bree");

    add_bree_desc("The road seems deserted as it runs northwest and " +
        "south. The only thing of interest is a stone wall " +
        "that is to the west.\n");

    set_add_outside_smiths();
    set_add_hill();

    add_exit(ROAD_DIR + "broad23", "northwest");
    add_exit(ROAD_DIR + "broad21", "south");
}
