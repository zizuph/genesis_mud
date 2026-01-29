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
    set_short("An old stone road by the coast");
    set_extraline(
        "The road runs west and east along the coast. The Sword Mountains rise "
        + "across the horizon to the west, while a forest lies to the north."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_sword_mountains("west");
    add_coast();
    add_sea("south");

    add_westwood("a short distance", "north");

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad06", "west");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad08", "east");
}
