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

    set_vbfc_extra(road_desc2);
    set_extraline("The road runs north and south as it crosses through " +
        "the grassland and meadows of the Southfarthing.");

    set_add_southfarthing();
    set_add_farms();

    add_exit(NS_RM_DIR + "road19", "northwest");
    add_exit(NS_RM_DIR + "road17", "southeast");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}
