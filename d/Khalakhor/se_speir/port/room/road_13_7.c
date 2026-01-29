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
        "The road is flanked on north and south sides " +
        "by stone walls, but a narrow trail leads " +
        "southwest between two buildings. One of those " +
        "buildings appears to be some sort of pub or " +
        "tavern, to the southeast.\n");

    add_exit(ROOM + "road_14_7", "east");
    add_exit(ROOM + "pub", "southeast");
    add_exit(ROOM + "road_12_8", "southwest");
    add_exit(ROOM + "road_12_7", "west");
}
