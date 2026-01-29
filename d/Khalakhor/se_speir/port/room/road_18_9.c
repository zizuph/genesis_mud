/*
 * This is the sixteenth room on first road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "north";
}

public void
create_road()
{
    set_short("harbourfront road");
    set_long("   You are at a corner of the road leading north " +
        "and west somewhere on the southern edge of Port " +
        "Macdunn, on the north shore of the harbour, Cala " +
        "Fasgadh. Most of the " +
        "town lies somewhere to the north, beyond the narrow " +
        "dirt road that threads its way between the warehouses " +
        "that way. The south side of the road " +
        "is just as densely packed with warehouses, evidence " +
        "of moderately heavy trading traffic in this town.\n");

    add_exit(ROOM + "road_18_8", "north");
    add_exit(ROOM + "road_17_9", "west");
}
