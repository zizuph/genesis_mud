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
        "village. The road is flanked on both sides " +
        "by high stone walls.\n");

    add_exit(ROOM + "road_8_4", "north");
    add_exit(ROOM + "road_8_6", "south");
}
