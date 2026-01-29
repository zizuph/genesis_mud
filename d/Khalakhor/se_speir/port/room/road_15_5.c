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
        "high stone wall, but the east side is " +
        "bordered by the shorter wall of a building " +
        "of some sort.\n");

    add_exit(ROOM + "road_15_4", "north");
    add_exit(ROOM + "road_15_6", "south");
}
