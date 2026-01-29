/*
* south_highroad/rooms/s_hroad01.c
* A room in the southern High Road, close to the City of Waterdeep
*
* Created Jan 2021 by Brine
*/

#pragma strict_types

#include "../defs.h"
inherit SOUTH_HIGHROAD_STD_ROOM;

int block_exit();

void
create_shr_room()
{
    set_short("A fork in the road");
    set_extraline(
        "The High Road runs west towards the coast and southeast towards an "
        + "elevated plateau, upon which sits the city of Waterdeep. The Long "
        + "Road forks off of it here, and continues northeast into the "
        + "Dessarin valley."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad13", "west");
    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad15", "southeast");
    add_exit("some_room", "northeast", block_exit);

    add_item(
        ({
            "long road", "Long Road", "the long road", "the Long Road",
            "fork", "fork in the road"
        }),
        "The road known locally as the \"Long Road\" splits off from the High "
        + "Road here, to make its way through the Dessarin valley and on "
        + "towards the city of Mirabar.\n"
    );

    add_item(
        ({
            "valley", "dessarin valley", "Dessarin valley", "vale",
            "dessarin vale", "lower dessarin vale", "Dessarin vale",
            "lower Dessarin vale"
        }),
        "The lower Dessarin vale lies to the northeast.\n"
    );
    add_waterdeep();
}

int
block_exit()
{
    write(
        "The road has been damaged by a recent flood, and cannot be travelled "
        + "at this time.\n"
    );
    return 1;
}
