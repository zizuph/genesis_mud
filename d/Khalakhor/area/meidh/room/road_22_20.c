/*
 * road_22_20.c
 *
 * This is part of a road in Meidh.
 *
 * Khail - February 2002
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;

public void
create_road()
{
    set_short("Trade Road");
    set_long("Trade road continues east and west, road to keep heads north, guardhouse south.\n");

    add_exit(ROOM + "road_21_20", "west");
    add_exit(ROOM + "road_22_21", "north");
    add_exit(ROOM + "road_23_20", "east");
    add_exit(ROOM + "guardhouse_22_19", "south");
}
