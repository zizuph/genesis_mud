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
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading " +
        "north and south near the middle of the " +
        "village. To the east is a small patch of " +
        "grass, to the west rises the outer wall of " +
        "a larger keep. The road empties out " +
        "south of here onto a larger road that leads " +
        "east and west.\n");

    add_exit(ROOM + "road_8_5", "north");
    add_exit(ROOM + "road_8_7", "south");
}
