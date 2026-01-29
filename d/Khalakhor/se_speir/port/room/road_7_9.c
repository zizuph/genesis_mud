/*
 * This is the fifth room on first road in Port Macdunn.
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
    set_long("   You are on a road leading east along " +
        "the southern edge of Port Macdunn, on the north " +
        "shore of the harbour, Cala Fasgadh. The town itself " +
        "rises to the north, beyond a narrow alley leading between " +
        "two buildings to the north. It's nothing " +
        "particularly amazing in size, but the large stone " +
        "buildings are well made, and the dirt roads well " +
        "maintained. To the south, you can see the numerous " +
        "piers of Port Macdunn jutting out into the waters of " +
        "Cala Fasgadh.\n");

    add_exit(ROOM + "road_7_8", "north");
    add_exit(ROOM + "road_8_9", "east");
    add_exit(ROOM + "road_6_9", "west");
}
