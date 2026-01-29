/*
 * road_22_21.c
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
    set_short("Dirt road");
    set_long("Dirt road south to trade road, north to plateau, temple door west, shop wall east.\n");

    add_exit(ROOM + "temple_21_21", "west");
    add_exit(ROOM + "road_22_22", "north");
    add_exit(ROOM + "road_22_20", "south");
}
