/*
 * North-South Road between Waymeet to Sarn Ford
 * By Finwe, January 2020
 */

#pragma strict_types

#include "../defs.h"
inherit "/d/Shire/ns_road/std/base_road.c";

void
create_road_room()
{

    set_areadesc("well travelled road");
    set_area("in central");
    set_areaname("Southfarthing");
    set_land("the Shire");
    set_areatype(0);

    set_vbfc_extra(road_desc1);
    set_extraline("The road runs north and south. Wildflowers and " +
        "bushes grow alongside the road. Farms can be seen in the " +
        "distance, in the lush green land.");

    set_add_westfarthing();
    set_add_farms();


    add_exit(NS_RM_DIR + "road20", "northwest");
    add_exit(NS_RM_DIR + "road18", "southeast");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}
