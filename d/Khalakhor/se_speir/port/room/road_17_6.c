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
    return "north";
}

public void
create_road()
{
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "north and south along the eastern " +
        "edge of the village. To the west a low " +
        "grassy hill rises in a clearing. Along the " +
        "east edge of the road, a wide earthen " +
        "embankment marks the edge of the village.\n");

    add_exit(ROOM + "road_17_5", "north");
    add_exit(ROOM + "road_17_7", "south");
}
