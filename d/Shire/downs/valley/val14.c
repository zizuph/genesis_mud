/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("valley");
    set_area("below");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("The valley follows a path that wanders around " +
        "the hills. The valley appears to be less open here from " +
        "the extra hills that are scattered about.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val13", "north");
    add_exit(VAL_DIR + "val15", "southeast");

}

