/*
 * road_22_23.c
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
    set_long("Dirt road south to trade road, north to plateau, building wall west, alley east.\n");

    add_exit(ROOM + "road_22_24", "north");
    add_exit(ROOM + "road_23_23", "east");
    add_exit(ROOM + "road_22_22", "south");
}
