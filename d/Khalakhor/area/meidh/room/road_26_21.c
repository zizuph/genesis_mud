/*
 * road_26_21.c
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
    set_short("trail");
    set_long("Dirt trail north and south, shop wall west, home wall east.\n");

    add_exit(ROOM + "road_26_22", "north");
    add_exit(ROOM + "road_26_20", "south");
}
