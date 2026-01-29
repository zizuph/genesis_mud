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
    set_long("   You are on a wide dirt road leading " +
        "north and south through the middle of the " +
        "village. The stone wall of a building rises " +
        "on the west, but a narrow road branches away " +
        "to the east from here. North of here, the " +
        "road opens up into a large four way intersection.\n");

    add_exit(ROOM + "road_12_1", "north");
    add_exit(ROOM + "road_13_2", "east");
    add_exit(ROOM + "road_12_3", "south");
}
