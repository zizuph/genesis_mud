/*
 * road_30_22.c
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
    set_long("Dirt road east and west, pub wall south, grey company door north.\n");

    add_exit(ROOM + "road_29_22", "west");
    add_exit(ROOM + "grey_company_30_23", "north");
    add_exit(ROOM + "road_31_22", "east");
}
