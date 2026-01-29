/*
 * road_25_20.c
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
    set_long("Trade road continues east and west, inn door north, alley south.\n");

    add_exit(ROOM + "road_24_20", "west");
    add_exit(ROOM + "inn_25_21", "north");
    add_exit(ROOM + "road_26_20", "east");
    add_exit(ROOM + "road_25_19", "south");
}
