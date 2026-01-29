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
        "north and south close to the eastern " +
        "edge of the village. The west side of the " +
        "road is flanked it's entire length by a " +
        "high stone wall, but a grassy hill rises " +
        "just to your east, and to the south you " +
        "can see the road ends at an intersection " +
        "which splits east and west.\n");

    add_exit(ROOM + "road_15_5", "north");
    add_exit(ROOM + "road_15_7", "south");
}
