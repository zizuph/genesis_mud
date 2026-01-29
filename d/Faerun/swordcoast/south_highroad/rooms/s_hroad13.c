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
        "The road rises along seabound cliffs to the northwest, while to the "
        + "east it runs inland."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_coast();
    add_sea("southwest");
    add_item(
        ({
            "cliff", "cliffs", "seabound cliff", "seabound cliffs"
        }),
        "Cliffs rise steeply along the coast to the west.\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad12", "northwest");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad14", "east");
}
