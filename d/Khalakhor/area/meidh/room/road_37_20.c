/*
 * road_37_20.c
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
    set_long("Trade road continues east and west, blacksmith wall north, watchtower door south.\n");

    add_exit(ROOM + "road_36_20", "west");
    add_exit(ROOM + "road_38_20", "east");
    add_exit(ROOM + "watchtower_37_19", "south");
}
