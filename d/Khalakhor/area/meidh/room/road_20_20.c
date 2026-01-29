/*
 * road_20_20.c
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
    set_long("Trade road through west gate of Old Town wall.\n");

    add_exit(ROOM + "road_19_20", "west");
    add_exit(ROOM + "road_21_20", "east");
}
