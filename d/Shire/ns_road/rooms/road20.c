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
    set_area("south of");
    set_areaname("Green Hills");
    set_land("the Westfarthing");
    set_areatype(0);

    set_vbfc_extra(road_desc4);
    set_extraline("The road runs north and south, and passes by the " +
        "village of Whitwell.");

    set_add_westfarthing();
    set_add_green_hills();

    add_item(({"whitwell", "whitewell"}),
        "It is a small settlement where the North South Road and the " +
        "Stock Road meet.\n");
    add_item(({"stock road"}),
        "The road is well travelled and runs east from the North " +
        "South Road. The Thain has closed it to visitors.\n");

    add_exit(NS_RM_DIR + "road21", "northwest");
    add_exit(NS_RM_DIR + "road19", "southeast");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}
