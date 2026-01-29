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

    set_extraline("The valley spits into different directions here. " +
        "One leads southwest while others lead around the barrows.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val12", "east");
    add_exit(VAL_DIR + "val10", "northwest");
    add_exit(VAL_DIR + "val08", "southwest");
}
