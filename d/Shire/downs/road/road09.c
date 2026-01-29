/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
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

    set_vbfc_extra(road_desc4);
    set_extraline("The grass is wet from the dew, making it " +
        "difficult to determine the paths in the grass.");
    set_add_wight_sounds();

    add_exit(ROAD_DIR + "road14", "south");
    add_exit(ROAD_DIR + "road06", "northwest");
}

