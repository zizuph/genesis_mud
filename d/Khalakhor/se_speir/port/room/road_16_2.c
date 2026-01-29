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
        "edge of the village. To the south, the road " +
        "is bordered by the wall of a stone building. " +
        "Along the north edge of the road, a wide " +
        "earthen embankment marks the edge of the " +
        "village. To the west, another road branches " +
        "off heading south. To the east, the road bends " +
        "sharply to the south.\n");

    add_exit(ROOM + "road_17_2", "east");
    add_exit(ROOM + "road_15_2", "west");
}
