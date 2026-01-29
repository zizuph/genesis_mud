/*
 * road_21_25.c
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
    set_long("Narrow trail north and east, building walls south and west.\n");

    add_exit(ROOM + "road_21_26", "north");
    add_exit(ROOM + "road_22_25", "east");
}
