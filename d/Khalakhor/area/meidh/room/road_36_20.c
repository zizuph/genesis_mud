/*
 * road_36_20.c
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
    set_long("Trade road continues east and west, blacksmith door north, guardhouse door south.\n");

    add_exit(ROOM + "road_35_20", "west");
    add_exit(ROOM + "blacksmith_36_21", "north");
    add_exit(ROOM + "road_37_20", "east");
    add_exit(ROOM + "guardhouse_36_19", "south");
}
