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
        "Foothills rise steeply to the northeast, leaning up to the "
        + "westernmost parts of the Sword Mountains. The road runs along the "
        + "coast to the northwest and into a valley to the east."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_foothills();
    add_sword_mountains("northeast");
    add_coast();
    add_sea("west");

    add_item(
        "valley",
        "A valley separates the peaks of the Sword Mountains to the east, "
        + "allowing passage between them.\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad02", "northwest");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad04", "east");
}
