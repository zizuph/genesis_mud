/*
* south_highroad/rooms/s_hroad01.c
* A room in the southern High Road, close to the City of Waterdeep
*
* Created Jan 2021 by Brine
*/

#pragma strict_types

#include "../defs.h"
inherit SOUTH_HIGHROAD_STD_ROOM;

void
create_shr_room()
{
    set_short("An old stone road at the foothills of the Sword Mountains");
    set_extraline(
        "Foothills rise steeply to the west, leaning up to the westernmost "
        + "parts of the Sword Mountains. The road runs into a valley to the "
        + "southwest, while towards the east it continues along the coast."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);
    
    add_foothills();
    add_sword_mountains("northwest");
    add_coast();
    add_sea("south");

    add_item(
        "valley",
        "A valley separates the peaks of the Sword Mountains to the southwest, "
        + "allowing passage between them.\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad05", "southwest");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad07", "east");
}
