/*
 * road_21_30.c
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
    set_long("Building door north, dirt trail south, building walls east and west.\n");

    add_exit(ROOM + "house_21_31", "north");
    add_exit(ROOM + "road_21_29", "south");
}
