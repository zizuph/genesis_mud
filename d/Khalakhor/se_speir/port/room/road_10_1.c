/**********************************************************************
 * - road_10_1.c                                                    - *
 * - This is part of a road in Port Macdunn.                        - *
 * - Created by Khail - May 16/97                                   - *
 **********************************************************************/

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
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "east and west along the northern " +
        "edge of the village. The north side of the " +
        "road is bordered by the low earthen embankment " +
        "which marks the edge of the village. To the " +
        "south stands the entrance into the " +
        "adventurer's guild.\n");

    add_exit(ROOM + "road_11_1", "east");
    add_exit(ROOM + "adv_guild", "south");
    add_exit(ROOM + "road_9_1", "west");
}
