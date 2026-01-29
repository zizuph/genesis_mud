/*
 * road_26_23.c
 *
 * This is part of a road in Meidh.
 *
 * Khail - March 2002
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public void
create_road()
{
    set_short("Dirt road");
    set_long("Dirt road west, north and south, building door east.\n");

    add_exit(ROOM + "road_25_23", "west");
    add_exit(ROOM + "road_26_24", "north");
    add_exit(ROOM + "building_27_23", "east");
    add_exit(ROOM + "road_26_22", "south");
}
