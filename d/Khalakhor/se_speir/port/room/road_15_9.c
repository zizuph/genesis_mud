/*
 * This is the thirteenth room on first road in Port Macdunn.
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
    set_short("harbourfront road");
    set_long("   You are on a road leading east and west along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. The town itself " +
        "rises to the north, behind the building creating a " +
        "stone wall on north side of the road. Large stone " +
        "warehouses rise to the south of the road here, " +
        "obscuring the view of the water.\n");

    add_exit(ROOM + "road_16_9", "east");
    add_exit(ROOM + "road_14_9", "west");
}
