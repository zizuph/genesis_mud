/*
 * road_21_20.c
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
    set_long("Trade road, watch tower entrance sorth, wall of a temple north, road continues east and west.\n");

    add_exit(ROOM + "road_20_20", "west");
    add_exit(ROOM + "watchtower_21_19", "south");
    add_exit(ROOM + "road_22_20", "east");
}
