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
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading east " +
        "and west through the interior of Port Macdunn. " +
        "To the south, the road is flanked by a low " +
        "stone wall, but the road branches to the " +
        "north. The wall on the west side of that " +
        "branch seems to run it's entire length, but " +
        "a small grassy hill rises on the " +
        "east side, just northeast of here.\n");

    add_exit(ROOM + "road_15_6", "north");
    add_exit(ROOM + "road_16_7", "east");
    add_exit(ROOM + "road_14_7", "west");
}
