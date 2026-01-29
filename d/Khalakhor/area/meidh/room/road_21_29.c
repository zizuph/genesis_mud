/*
 * road_21_29.c
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
    set_short("Narrow trail");
    set_long("Narrow trail north and south, building walls east and west.\n");

    add_exit(ROOM + "road_21_30", "north");
    add_exit(ROOM + "road_21_28", "south");
}
