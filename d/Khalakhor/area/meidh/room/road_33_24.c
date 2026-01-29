/*
 * road_33_24.c
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
    set_long("Dirt road east and west, building wall north, garden fence south.\n");

    add_exit(ROOM + "road_32_24", "west");
    add_exit(ROOM + "road_34_24", "east");
}
