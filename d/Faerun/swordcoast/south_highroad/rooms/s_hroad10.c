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
    set_short("An old stone road by some cliffs");
    set_extraline(
        "The road runs west and southeast along the coast. A forest lies off "
        + "to the north. To the south, tall cliffs drop off into the sea."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_coast();
    add_sea("south");
    add_westwood("off", "north");
    add_redcliffs();
    add_red_rocks();

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad09", "west");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad11", "southeast");
}

public void
init()
{
    ::init();

    init_cliff_room();
}
