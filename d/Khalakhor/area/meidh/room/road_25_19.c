/*
 * road_25_19.c
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
    set_short("trail");
    set_long("Dirt trail north, bank door west, house wall east, old wall south.\n");

    add_exit(ROOM + "bank_24_19", "west");
    add_exit(ROOM + "road_25_20", "north");
}
