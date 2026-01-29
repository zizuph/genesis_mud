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
    set_area("of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("The path leads north and south between many " +
        "rolling hills. The hills are scattered about the valley " +
        "and grass covered.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val06", "south");
    add_exit(VAL_DIR + "val08", "northeast");

}

