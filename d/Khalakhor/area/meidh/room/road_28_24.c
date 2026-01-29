/*
 * road_28_24.c
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
    set_long("Dirt road east and south, grey company east, plateau north.\n");

    add_exit(ROOM + "road_27_24", "west");
    add_exit(ROOM + "road_28_23", "south");
}
