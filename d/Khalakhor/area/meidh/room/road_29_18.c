/*
 * road_29_18.c
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
    set_long("Highland road through south gate in old wall.\n");

    add_exit(ROOM + "road_29_19", "north");
    add_exit(ROOM + "road_29_17", "south");
}
