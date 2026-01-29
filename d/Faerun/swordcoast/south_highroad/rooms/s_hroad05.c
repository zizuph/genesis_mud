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
    set_short("An old stone road through a valley");
    set_extraline(
        "The road runs west and northeast through the valley. On either side "
        + "of the road rises a craggy peak, towering over you."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_sword_mountains("north");

    add_item(
        ({
            "crag", "crags", "peak", "peaks", "craggy peak", "craggy peaks",
            "mountain", "mountains", "jagged crags", "sword mountains",
            "Sword Mountains", "the sword mountains", "the Sword Mountains",
            "southern sword mountains", "southern Sword Mountains"
        }),
        "Two craggy peaks beset the road, one to the north and one to the "
        + "south.\n"
    );

    add_item(
        ({
            "mount sar", "mnt sar", "Mount Sar", "Mnt Sar", "northern crag",
            "northern peak", "northern craggy peak", "first crag", "first peak",
            "first craggy peak", "northern mountain", "first mountain",
            "north mountain", "north peak", "north craggy peak"
        }),
        "To the north rises a tall mountain, known to the local populace as \""
        + "Mount Sar\". Its jagged, craggy peak almost appears able to scratch "
        + "the sky.\n"
    );

    add_item(
        ({
            "mount helimbrar", "mnt helimbrar", "Mount Helimbrar",
            "Mnt Helimbrar", "southern crag", "southern peak",
            "southern craggy peak", "second crag", "second peak",
            "second craggy peak", "southern mountain", "second mountain",
            "south mountain", "south peak", "south craggy peak"
        }),
        "To the south rises a tall mountain, known to the local populace as \""
        + "Mount Helimbrar\". It is jagged and craggy, but appears somewhat "
        + "more rounded than the peak to the north.\n"
    );

    add_item(
        "valley",
        "The valley carves its path between the jagged crags of the southern "
        + "Sword Mountains, leading way for the High Road.\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad04", "west");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad06", "northeast");
}
