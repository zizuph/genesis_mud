/*
 * road_28_21.c
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
    set_long("Dirt trail north and south, inn wall west, pub wall east.\n");

    add_exit(ROOM + "road_28_22", "north");
    add_exit(ROOM + "road_28_20", "south");
}
