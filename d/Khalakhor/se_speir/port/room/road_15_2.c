/*
 * This is part of a road in Port Macdunn.
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
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "east and west along the northern " +
        "edge of the village. Another wider road heads " +
        "south from here, between two stone buildings. " +
        "Along the north edge of the road, a wide " +
        "earthen embankment marks the edge of the " +
        "village.\n");

    add_exit(ROOM + "road_16_2", "east");
    add_exit(ROOM + "road_15_3", "south");
    add_exit(ROOM + "road_14_2", "west");
}
