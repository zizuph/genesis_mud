/*
 * This is an alley harbour master's office and
 * tavern in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"

inherit "/d/Khalakhor/std/room";

public int *
query_local_coords()
{
    return ({12,8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
create_khalakhor_room()
{
    set_short("narrow alley");
    set_long("   You are in a narrow, shadowed alley between two " +
        "windowless stone buildings. The road here shows " +
        "little evidence of heavy use, though the grass " +
        "is quite heavily matted from some traffic. To " +
        "the south, the alley opens up onto a small " +
        "patch of grass, and beyond that the Cala Fasgadh.\n");

    add_exit(ROOM + "road_13_7", "northeast");
    add_exit(ROOM + "road_12_9", "south");
    add_exit(ROOM + "road_11_9", "southwest");
}
