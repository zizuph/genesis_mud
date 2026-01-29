/*
 * road_32_19.c
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
    set_short("path");
    set_long("Narrow dirt trail between buildings, guardhouse door west, trade road north, armourer wall east, old wall south.\n");

    add_exit(ROOM + "home_31_19", "west");
    add_exit(ROOM + "road_32_20", "north");
}
