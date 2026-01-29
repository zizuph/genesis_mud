/*
 * road_31_24.c
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
    set_long("Dirt road east and south, plateau north, grey company wall west.\n");

    add_exit(ROOM + "road_32_24", "east");
    add_exit(ROOM + "road_31_23", "south");
}
