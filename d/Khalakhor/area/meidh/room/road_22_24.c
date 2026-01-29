/*
 * road_22_24.c
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
    set_long("Dirt road south to trade road, north to plateau, building wall west and east.\n");

    add_exit(ROOM + "road_22_25", "north");
    add_exit(ROOM + "road_22_23", "south");
}
