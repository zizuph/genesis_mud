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

    set_vbfc_extra(road_desc4);
    set_extraline("The " + areadesc + " travels east and west past Longbottom.");

    set_add_southfarthing();
    set_add_farms();
    add_longbottom_descr();

    add_exit(NS_RM_DIR + "road09", "west");
    add_exit(NS_RM_DIR + "road08a", "east");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}
