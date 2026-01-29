/*
 * road_33_20.c
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
    set_long("Trade road continues east and west, adv. guild wall north, armourer door south.\n");

    add_exit(ROOM + "road_32_20", "west");
    add_exit(ROOM + "road_34_20", "east");
    add_exit(ROOM + "armourer_33_19", "south");
}
