/*
 * road in Esgaroth
 * By Finwe, March 2001
 */
 
#pragma strict_types
 
#include "../local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc1);
    set_extraline("A tall barrow rises to the west, forcing the " +
        "path to go around it.");
    set_add_wight_sounds();

    add_exit(ROAD_DIR + "road22", "south");
    add_exit(ROAD_DIR + "road16", "northwest");
}

