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
        "edge of the village. The north side of the " +
        "road is bordered by the low earthen embankment " +
        "which marks the edge of the village. To the " +
        "south stands the entrance into the post office.\n");

    add_exit(ROOM + "road_10_1", "east");
    add_exit(ROOM + "post", "south");
    add_exit(ROOM + "road_8_1", "west");
}
