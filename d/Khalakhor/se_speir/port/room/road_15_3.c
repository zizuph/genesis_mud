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
        "road is flanked its entire length by a " +
        "high stone wall, and appears to offer no " +
        "means of entry. On the east side of the " +
        "road, a low stone building stands. " +
        "Sturdily constructed and apparently visited " +
        "frequently, it would seem you have found " +
        "the village shop.\n");

    add_exit(ROOM + "road_15_2", "north");
    add_exit(ROOM + "shop", "east");
    add_exit(ROOM + "road_15_4", "south");
}
