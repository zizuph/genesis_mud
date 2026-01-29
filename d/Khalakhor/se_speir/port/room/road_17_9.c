/*
 * This is the fifteenth room on first road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "east";
}

public void
create_road()
{
    set_short("harbourfront road");
    set_long("   You are on a road leading east and west along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. Most of the " +
        "town lies somewhere to the north, on the far other " +
        "side of the high stone warehouses which stand on " +
        "that side of the road. The south side of the road " +
        "is just as densely packed with warehouses, evidence " +
        "of moderately heavy trading traffic in this town.\n");

    add_exit(ROOM + "road_18_9", "east");
    add_exit(ROOM + "road_16_9", "west");
}
