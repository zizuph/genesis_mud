/*
 * road_28_22.c
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
    set_long("Dirt road north south east and west.\n");

    add_exit(ROOM + "road_27_22", "west");
    add_exit(ROOM + "road_28_23", "north");
    add_exit(ROOM + "road_29_22", "east");
    add_exit(ROOM + "road_28_21", "south");
}
