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
        "north and south through the middle of the " +
        "village. Low stone walls, either of very " +
        "long buildings or compounds of some sort, " +
        "flank the road on either side. To the north " +
        "you notice a smaller road branching away " +
        "eastwards from this one.\n");

    add_exit(ROOM + "road_12_2", "north");
    add_exit(ROOM + "road_12_4", "south");
}
