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
        "With the exception of a grassy clearing " +
        "to the north, the road is fairly well enclosed by " +
        "the walls of various buildings in all directions.\n");

    add_exit(ROOM + "road_12_7", "east");
    add_exit(ROOM + "road_10_7", "west");
}
