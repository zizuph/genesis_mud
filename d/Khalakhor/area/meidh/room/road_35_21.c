/*
 * road_35_21.c
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
    set_short("dirt road");
    set_long("Road with trade road to south, plateau to north, herbalist door west, blacksmith wall east.\n");

    add_exit(ROOM + "herbalist_34_21", "west");
    add_exit(ROOM + "road_35_22", "north");
    add_exit(ROOM + "road_35_20", "south");
}
