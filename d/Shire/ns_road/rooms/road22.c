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
    set_areaname("Waymeet"); 
    set_land("Westfarthing");
    set_areatype(0);

    set_vbfc_extra(road_desc1);
    set_extraline("The road runs south through Westfarthing and " +
        "north to the town of Waymeet. ");

    set_add_westfarthing();
    set_add_green_hills();    

    add_exit("/d/Shire/waymeet/rooms/streets/street_10.c", "north");
    add_exit(NS_RM_DIR + "road21", "southeast");

    reset_shire_room(); 
}

void reset_shire_room()
{
    set_searched(0);
}
