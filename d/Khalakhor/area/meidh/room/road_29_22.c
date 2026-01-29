/*
 * road_29_22.c
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
    set_long("Dirt road east and west, pub wall south, grey company wall north.\n");

    add_exit(ROOM + "road_28_22", "west");
    add_exit(ROOM + "road_30_22", "east");
}
