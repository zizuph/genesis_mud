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
        "east and south along the northern " +
        "edge of the village. On the inside edge of " +
        "the turn, the road is bordered by the wall " +
        "of a stone building. Along the outer edge, " +
        "a wide earthen embankment marks the limits " +
        "of the village.\n");

    add_exit(ROOM + "road_9_1", "east");
    add_exit(ROOM + "road_8_2", "south");
}
