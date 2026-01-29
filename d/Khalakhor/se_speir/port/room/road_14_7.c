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
        "by stone walls, which block out the view " +
        "completely in those directions.\n");

    add_exit(ROOM + "road_15_7", "east");
    add_exit(ROOM + "road_13_7", "west");
}
