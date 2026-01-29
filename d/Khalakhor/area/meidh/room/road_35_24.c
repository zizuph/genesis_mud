/*
 * road_35_24.c
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
    set_long("Dirt road west, north and south, building wall east.\n");

    add_exit(ROOM + "road_34_24", "west");
    add_exit(ROOM + "road_35_25", "north");
    add_exit(ROOM + "road_35_23", "south");
}
