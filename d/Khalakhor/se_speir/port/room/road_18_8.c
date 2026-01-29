/*
 * This is the seventeenth room on first road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "northwest";
}

public void
create_road()
{
    set_short("dirt road");
    set_long("   You are on a short stretch of dirt road that " +
        "threads its way between closely-spaced warehouses " +
        "in the southeast section of Port Macdunn. It looks " +
        "like it may open up considerably towards the north" +
        "west, however. Here, the tall stone warehouses " +
        "block out the view of most anything except the sky " +
        "and the dirt at your feet.\n");

    add_exit(ROOM + "road_17_7", "northwest");
    add_exit(ROOM + "road_18_9", "south");
}
