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

    set_vbfc_extra(road_desc4);
    set_extraline("You stand between two tall barrows that rise " +
        "to the north and southwest of you. Some mists flow off " +
        "their crests towards you.");
    set_add_wight_sounds();


    add_exit(DOWNS_DIR + "road25", "southwest");
    add_exit(DOWNS_DIR + "road22", "north");
}

