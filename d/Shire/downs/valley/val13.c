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

    set_extraline("The Barrows stand above you as the valley " +
        "stretches northwest and south. In the valley are other " +
        "grass covered hills.");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val14", "south");
    add_exit(VAL_DIR + "val12", "northwest");

}

