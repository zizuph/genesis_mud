/*
 * road_38_20.c
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
    set_short("Trade Road");
    set_long("At east gate of old wall, Trade road continues east and west.\n");

    add_exit(ROOM + "road_37_20", "west");
    add_exit(ROOM + "road_39_20", "east");
}
