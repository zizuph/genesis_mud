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

    set_extraline("You stand on a hill overlooking the valley. " +
        "The hill is rounded by the centuries of blowing winds " +
        "that frequent the valley.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val11", "northeast");
    add_exit(VAL_DIR + "val07", "southwest");

}

