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
    set_areadesc("well tended orchard");
    set_area("in central");
    set_areaname("Southfarthing");
    set_land("the Shire");
    set_areatype(0);

    add_exit(NS_RM_DIR + "road17", "northwest");
    add_exit(NS_RM_DIR + "road15", "southeast");

    set_vbfc_extra(road_desc3);
//    set_extraline("The grasslands of Southfarthing spreadout in all " +
//        "directions. It is dotted with farms in the distance.");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}
