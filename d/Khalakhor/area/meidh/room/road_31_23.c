/*
 * road_31_23.c
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
    set_long("Dirt road north and south, adventurer's guild wall east, grey company wall west.\n");

    add_exit(ROOM + "road_31_24", "north");
    add_exit(ROOM + "road_31_22", "south");
}
