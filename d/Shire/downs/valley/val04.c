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
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("The land is bare in the midst of some hills. " +
        "The valley passes between the grass covered hills and " +
        "spreads out in all directions.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val05", "north");
    add_exit(VAL_DIR + "val03", "south");

}

