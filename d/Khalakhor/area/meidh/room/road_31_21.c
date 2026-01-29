/*
 * road_31_21.c
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
    set_long("Dirt alley going north and south, pub wall west, adventurer's guild wall east.\n");

    add_exit(ROOM + "road_31_22", "north");
    add_exit(ROOM + "road_31_20", "south");
}
