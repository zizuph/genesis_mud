/*
 * road_29_19.c
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
    set_short("Highland Road");
    set_long("Highland road north and south, home wall west, watchtower door east.\n");

    add_exit(ROOM + "road_29_20", "north");
    add_exit(ROOM + "watchtower_30_19", "east");
    add_exit(ROOM + "road_29_18", "south");
}
