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
        "The road forms a T-intersection here, with a " +
        "stretch leading away southwards between the " +
        "stone buildings housing the harbour master and local " +
        "bladesmith. Beyond them, the road leads to the " +
        "piers jutting out into the harbour, Cala " +
        "Fasgadh. The road is fairly well enclosed by " +
        "the walls of various buildings in all directions.\n");
        
    add_exit(ROOM + "road_8_7", "west");
    add_exit(ROOM + "road_10_7", "east");
    add_exit(ROOM + "road_9_8", "south");
    add_exit(ROOM + "archives", "north");

}
