/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc2);
    set_extraline("The fog grows unusually deeper as you walk " +
        "through them here.");
    set_add_wight_sounds();

    add_exit(DOWNS_DIR + "road18", "east");
    add_exit(DOWNS_DIR + "road14", "northwest");
}

