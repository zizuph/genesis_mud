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
        "The road runs west and east along the coast. A forest lies to the "
        + "north, while the Sea of Swords lies to the south. You spot "
        + "countless tiny islets just south of the coast."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_coast();
    add_sea("south");

    add_westwood("a short distance", "north");

    add_item(
        ({
            "stacks", "sea stacks", "islets", "boulder", "boulders", "rocks",
            "tiny islets", "islet", "stack", "sea stack", "tiny islet"
        }),
        "Just off the coast to the south are hundreds, if not thousands, of "
        + "tiny islets. Most are sea stacks of various sizes, carved by the "
        + "relentless waves of the Sea of Swords, while some are mere boulders "
        + "that barely peek up above the waves. This surely makes for a "
        + "treacherous stretch of water.\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad07", "west");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad09", "east");
}
